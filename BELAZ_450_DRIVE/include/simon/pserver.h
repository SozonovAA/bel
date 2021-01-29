/*******************************************************************************

    pserver.h - concurrent server support

    this module provides easy to use support for parallel servers ( concurrent
    server).

    Revision see net.h
    Company  D.SignT
    Author   Claus Hermbusche
    Created  23 Sep 2002

    Hardware D.Module.91C111
             D.Module.8900
             C.Module.ODEM
             DSK91C111

    Compiler VC33: Code Composer Studio
                   Version: 1.1
             C6x:  Code Composer Studio
                   Version: 2.x
             C5x:  Code Composer Studio
                   Version: 2.x
             21065: Visual DSP 1.0
                    Visual DSP++ 2.0
                    Visual DSP++ 3.0

    Options  VC33:
             C6x:
             21065: -D _ADSP21065

    History

    1.1 23 Jul 2004 CH
        new method get_actual() for using in callback functions.
    1.0 initial release 23 Sep 2002 by CH


    Problem: After connecting a listening socket, this socket cannot be reached
    from any other client until it is disconnected:

    Server before connecting:
        192.168.168.100
     -------------------------
    |                          |
    |       *==========*       |
    |       *  Server  *       |
    |       *==========*       |
    |  {192.168.168.100 : 21}  |---> listening socket
    |  { * . * . * . *  : * }  |---> accept all clients
    |                          |
     -------------------------

    Server after connecting:
        192.168.168.100
     --------------------------                  --------------------------
    |                          |                |                          |
    |       *==========*       |                |       *==========*       |
    |       *  Server  *       |   connected    |       *  Client  *       |
    |       *==========*       |<-------------->|       *==========*       |
    |  {192.168.168.100 : 21}  |                |  {192.168.168.200 :1550} |
    |  {192.168.168.200 :1550} |                |  {192.168.168.100 : 21}  |
    |                          |                |                          |
     --------------------------                  -------------------------- 


    On operating systems like linux there is a possibility to call a system
    function like 'fork()' to create a runtime copy of the listening server.
    Without an OS we have two other possible ways to handle concurrent servers.
    First we can define a static list with i.e. 10 sockets. Second we can use
    a dynamic linked list. The static list needs much more data memory, on the
    other hand the dynamic list needs more code for administration.
    This module provides an easy to use support for the dynamic version of
    parallel servers.
    After connecting an listening server a new server can be added to the
    server-list:

    Server after connecting:
        192.168.168.100
     --------------------------                  --------------------------
    |                          |                |                          |
    |       *==========*       |                |       *==========*       |
    |       *  Server  *       |   connected    |       *  Client  *       |
    |       *==========*       |<-------------->|       *==========*       |
    |  {192.168.168.100 : 21}  |                |  {192.168.168.200 :1550} |
    |  {192.168.168.200 :1550} |                |  {192.168.168.100 : 21}  |
    |                          |                |                          |
    |                          |                 -------------------------- 
    |       *==========*       |
    |       *  Server  *       |   listening
    |       *==========*       |<--------------
    |  {192.168.168.100 : 21}  |
    |  { * . * . * . *  : * }  |
    |                          |
     --------------------------

    The maximum number of servers is limited by available memory only

    Using parallel server:
    The user defined function 'init_parallel_echo_server()' must be called once
    to have at least one listening socket. After connecting this socket, the
    callback function tcp_echo() is called from TCP stack with error code
    SO_CONNECTION_ESTABLISHED. The next 'init_parallel_echo_server()' function
    call increases the server list. The new opened server socket is automatically
    in listening state and can be connected from the next client. After dis-
    connecting one client, the TCP stack calls the user callback function again.
    This time with error code SO_CONNECTION_CLOSED (or SO_CONNECTION_RESETTED).
    Call 'close_parallel_echo_server()' to decrease the server list and free
    all associated memory.


*******************************************************************************/
    

/*******************************************************************************
 _PARALLEL_SERVER type definition
*******************************************************************************/
typedef struct _p_server
{
    void   *info;           /* protocol information (FTP,HTTP,user defined)   */
    SOCKET *server;         /* listening socket                               */
    int32_t state;          /* state for this server connection               */
    int32_t close;          /* flag for closing connection                    */

    void   **finfo;         /* file information                               */
  
    struct _p_server *next; /* double linked list next entry                  */
    struct _p_server *prev; /* double linked list privious entry              */

} _PARALLEL_SERVER;

/*******************************************************************************
 pserver function addresses are assigned at runtime
*******************************************************************************/
typedef struct
{
    _PARALLEL_SERVER *(*add) (u_int16_t, _PARALLEL_SERVER **);
    _PARALLEL_SERVER *(*get_next) (_PARALLEL_SERVER *, _PARALLEL_SERVER **);
    _PARALLEL_SERVER *(*close) (_PARALLEL_SERVER *, _PARALLEL_SERVER **);
    _PARALLEL_SERVER *(*get_actual) (SOCKET *, _PARALLEL_SERVER **);

} pserver_function_types;


#ifdef __cplusplus
extern "C" {
#endif /* !__cplusplus */

/*******************************************************************************

    Function  add_pserver()

    Parameter

    Returns   new pointer to a parallel server structure
              or NULL - out of memory

    Calls

*******************************************************************************/
_PARALLEL_SERVER *add_pserver (u_int16_t proto,
                               _PARALLEL_SERVER **pserver_head);

/*******************************************************************************

    Function get_actual_pserver()

    search pserver list for actual socket

    Parameter  *so           - connected socket
              **pserver_head - user defined list head

    Returns   pointer to the next list entry

    Calls     -

*******************************************************************************/
_PARALLEL_SERVER *get_actual_pserver (SOCKET *so,
                                      _PARALLEL_SERVER **pserver_head);

/*******************************************************************************

    Function get_next_pserver

    Parameter
    Returns
    Calls

*******************************************************************************/
_PARALLEL_SERVER *get_next_pserver (_PARALLEL_SERVER *pserver,
                                    _PARALLEL_SERVER **pserver_head);

/*******************************************************************************

    Function close_pserver()

    Parameter pserver  - server to close

    Returns   always NULL

    Calls

*******************************************************************************/
_PARALLEL_SERVER *close_pserver (_PARALLEL_SERVER *pserver,
                                 _PARALLEL_SERVER **pserver_head);


#ifdef __cplusplus
} // extern "C"
#endif
