#define __LW_IP_C

/* Includes ------------------------------------------------------------------*/
#include "lwip/memp.h"
#include "LwIP.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"
#include "lwip/tcpip.h"
#include "lwip/inet.h"
#include "netif/etharp.h"
#include "lwip/dhcp.h"
#include "lwip/tcp_impl.h"
#include "ethernetif.h"
#include "stm32f10x.h"
#include "arch/sys_arch.h"
#include <stdio.h>
#include "stm32_eth.h"
#include "cfg.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MAX_DHCP_TRIES        4
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static struct netif netif;
static uint32_t IPaddress = 0;
u32 TCPTimer=0;			//TCP��ѯ��ʱ��
u32 ARPTimer=0;			//ARP��ѯ��ʱ��
u32 lwip_localtime;		//lwip����ʱ�������,��λ:ms
/* Private function prototypes -----------------------------------------------*/
static void TcpipInitDone(void *arg);
static void list_if(void);

/* Private functions ---------------------------------------------------------*/

/** 
 * @brief TcpipInitDone wait for tcpip init being done
 * 
 * @param arg the semaphore to be signaled
 */
static void TcpipInitDone(void *arg)
{
    sys_sem_t *sem;
    sem = arg;
    sys_sem_signal(sem);
}

/** 
 * @brief Display_IPAddress Display IP Address
 * 
 */
void Display_IPAddress(void)
{
    if(IPaddress != netif.ip_addr.addr)
    {   /* IP ��ַ�����ı�*/
        __IO uint8_t iptab[4];
        uint8_t iptxt[20];
        
        /* read the new IP address */
        IPaddress = netif.ip_addr.addr;
        
        iptab[0] = (uint8_t)(IPaddress >> 24);
        iptab[1] = (uint8_t)(IPaddress >> 16);
        iptab[2] = (uint8_t)(IPaddress >> 8);
        iptab[3] = (uint8_t)(IPaddress);
        
        sprintf((char*)iptxt, "   %d.%d.%d.%d    ", iptab[3], iptab[2], iptab[1], iptab[0]);
        
        list_if();                           
    }
#if LWIP_DHCP
    else if(IPaddress == 0)
    {   // �ȴ�DHCP����IP
        
        /* If no response from a DHCP server for MAX_DHCP_TRIES times */
        /* stop the dhcp client and set a static IP address */
        if(netif.dhcp->tries > MAX_DHCP_TRIES) 
        {   /* ����DHCP���Դ��������þ�̬IP���� */
            struct ip_addr ipaddr;
            struct ip_addr netmask;
            struct ip_addr gw;
            
            dhcp_stop(&netif);
            
            IP4_ADDR(&ipaddr, 10, 21, 11, 245);
            IP4_ADDR(&netmask, 255, 255, 255, 0);
            IP4_ADDR(&gw, 10, 21, 11, 254);
            
            netif_set_addr(&netif, &ipaddr , &netmask, &gw);
            
            list_if();
        }
    }
#endif
}

/**
* @brief display ip address in serial port debug windows
*/
static void list_if()
{
    myPrintf("Default network interface: %c%c\n", netif.name[0], netif.name[1]);
    myPrintf("ip address: %s\n", inet_ntoa(*((struct ip_addr_t*)&(netif.ip_addr))));
    myPrintf("gw address: %s\n", inet_ntoa(*((struct ip_addr_t*)&(netif.gw))));
    myPrintf("net mask  : %s\n", inet_ntoa(*((struct ip_addr_t*)&(netif.netmask))));
}

/**
* @brief Init_LwIP initialize the LwIP
*/

void Init_LwIP(void)
{
    struct ip_addr ipaddr;
    struct ip_addr netmask;
    struct ip_addr gw;
    uint8_t macaddress[6]={0,0,0,0,0,1};
    
    sys_sem_t sem;
    
    sys_init();
    
    /* Initializes the dynamic memory heap defined by MEM_SIZE.*/
    mem_init();
    
    /* Initializes the memory pools defined by MEMP_NUM_x.*/
    memp_init();
    
    pbuf_init();
    netif_init();
    
//    printf("TCP/IP initializing... \r\n");
	sys_sem_new(&sem, 0);
    tcpip_init(TcpipInitDone, &sem);
    sys_sem_wait(&sem);
    sys_sem_free(&sem);
//    printf("TCP/IP initialized. \r\n");

#if LWIP_DHCP
    /* ����DHCP������ */
    ipaddr.addr = 0;
    netmask.addr = 0;
    gw.addr = 0;
#else
    /* ���þ�̬IP */
//  IP4_ADDR(&ipaddr, 192, 168, 1, 197);
//  IP4_ADDR(&netmask, 255, 255, 255, 0);
//  IP4_ADDR(&gw, 192, 168, 1, 1);
	 DEF_NET_IP1
//	  IP4_ADDR(&ipaddr, 192, 168, 33, 11);
//  IP4_ADDR(&netmask, 255, 255, 0, 0);
//  IP4_ADDR(&gw, 192, 168, 0, 1);
#endif
    
    Set_MAC_Address(macaddress);
    
    netif_add(&netif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);
    netif_set_default(&netif);
    
#if LWIP_DHCP
    dhcp_start(&netif);
#endif
    netif_set_up(&netif);
}

/**
* @brief  Ethernet ISR
*/
void LwIP_Pkt_Handle(void)
{
  /* Read a received packet from the Ethernet buffers and send it to the lwIP for handling */
  ethernetif_input(&netif);
}

void LwIP_Periodic_Handle(void)
{

  /* TCP periodic process every 250 ms */
  if (lwip_localtime - TCPTimer >= TCP_TMR_INTERVAL)
  {
    TCPTimer =  lwip_localtime;
    tcp_tmr();
  }
  /* ARP periodic process every 5s */
  if (lwip_localtime - ARPTimer >= ARP_TMR_INTERVAL)
  {
    ARPTimer =  lwip_localtime;
    etharp_tmr();
  }

#if LWIP_DHCP
  /* Fine DHCP periodic process every 500ms */
  if (lwip_localtime - DHCPfineTimer >= DHCP_FINE_TIMER_MSECS)
  {
    DHCPfineTimer =  lwip_localtime;
    dhcp_fine_tmr();
  }
  /* DHCP Coarse periodic process every 60s */
  if (lwip_localtime - DHCPcoarseTimer >= DHCP_COARSE_TIMER_MSECS)
  {
    DHCPcoarseTimer =  lwip_localtime;
    dhcp_coarse_tmr();
  }
#endif

}
