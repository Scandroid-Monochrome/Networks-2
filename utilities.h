#define TRUE 1
#define FALSE 0

#define SEND_MESSAGE 0
#define WAIT_FOR_ACK 1

#define TIMER_TIME 100

//structure for putting incoming message passed in parameter of function 
//A_output() into a linked list, so that when the ack of the previous 
//sending message arrives, the first message in linked list would be 
//packed and sent from the sender, if there is one 
struct msgQueue { 
        struct msg waitingMessage; 
        struct msgQueue *next; 
};

//Structure for storing sent packets, so once timer runs out the 
//last packet can be fetched from the linked list and sent again
struct pktQueue {
    struct pkt bufferedPkt; 
    struct pktQueue *next;
};

int seq_num;
int ack_num;

struct msgQueue *head;
struct pktQueue *pktBufferHead;

struct msg *last_message;
struct pkt *last_packet;

struct message_state {
    int state;
};

struct pkt* message_to_packet(struct msg *p_message, int seqnum, int acksum);

struct msg* packet_to_message(struct pkt *p_packet);

void copyPacket(struct pkt endP, struct pkt initP);

void copyMessage(struct msg endM, struct msg initM);

void sendLastPacket();

int calculateChecksum(char* vdata, int acknum, int seqnum);

struct pkt* make_packet(char payload[20], int seqnum, int acknum, int checksum);

int packetNotCorrupt(struct pkt* test_packet);

int isCorrectPacket(struct pkt* packet);

int calculateChecksumForResponse(int seqnum, int acknum);

void toggle_0_1(int* p_number);

void debugLog(char* function_name, char* log_message);