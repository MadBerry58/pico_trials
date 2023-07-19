#include "devSM/devSM.h"
#include "../../picoOS/picoOS.h"

#define NODE_ID 1u //Node IDs wil be given by the user/configuration sw

void main()
{
    NodeType_e node_type = Development;
    /* Initialize base OS functionality */
    init_OS(node_type, NODE_ID);

    /* Initialize node-specific functionality on core 1 */
    init_devNodeSM();

    /* Start the OS and trigger the node scheduler loop */
    run_OS();

}