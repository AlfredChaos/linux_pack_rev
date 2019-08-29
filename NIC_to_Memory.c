#include <stdio.h>

#define MAX 1500
char *Memroy[MAX];
CPU cpu;
NIC nic;

typedef struct 
{
    /* data */
    char *dstMAC;
    char *srcMAC;
    int type;
    char *checksum;
    char *data;
}ethHeader;

typedef struct 
{
    /* data */
    char *version;      //4 bit version
    int header_length;  //4 bit
    char *tos;          //type of service 8 bit
    int length;         //total length 16 bit
    char *flag;         //16 bit
    char *logo;         //3 bit
    char *move;         //13 bit
    char *TTL;          //8 bit
    char *checksum;     //16 bit
    char *srcIP;        //32 bit
    char *dstIP;        //32 bit
}ipHeader;

typedef struct 
{
    /* data */
    int srcPort;
    int dstPort;
    int length;
    char *checksum;
    char *data;
}udpHeader;

typedef struct 
{
    /* data */
    char *dstMAC;
    char *srcMAC;
    char *srcIP;  
    char *dstIP; 
    int srcPort;
    int dstPort;
    char *data;
}Package;

typedef struct
{
    /* data */
    char uuid[32];
    char *mac;
    char *mode;
    int DMA;
    struct Package *package;
    char *ip;
    int IRQ;
}NIC;

typedef struct 
{
    /* data */
    int IRQ;
}CPU;

void init_Any() {
    NIC nic = {
        mac: "52:56:FF:58:41:C5", 
        mode: "promiscuous", 
        DMA: 1, 
        package: NULL, 
        ip: "192.168.1.2",
        IRQ: 1,
    };

    Package package = 
    {
        dstMAC: "52:56:FF:58:41:C5",
        srcMAC: "52:56:FF:58:41:C6",
        srcIP:  "192.168.1.3",
        dstIP:  "192.168.1.2",
        srcPort: 8080,
        dstPort: 80,
    };
}

void package_comein(Package *package) {
    if (package != NULL) {
        nic.package = package;
    }
    if (nic.package != NULL && nic.mode != "promiscuous" && package->dstMAC != nic.mac) {
        nic.package == NULL;
    }
    if (nic.IRQ == 1) {
        sendIRQtoCPU();
    }else if (nic.IRQ == 0) {
        DMA(*package);
    }else {
        printf("IRQ error");
    }
    cpu_work();
}

void run_IRQ_handler() {
    nic_Driver();
}

void nic_Driver() {
    nic.IRQ = 0;
    raise_soft_IRQ();
}

void cpu_work() {
    if (cpu.IRQ == 1) {
        run_IRQ_handler();
    }
}

void DMA(Package package) {
    int i = 0;
    Memroy[i++] = &package;
}

void sendIRQtoCPU() {
    cpu.IRQ = 1;
}


