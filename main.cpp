#include <iostream>
#include "xpipe.h"
#include "jobserver.h"
#include "asyntabworker.h"
using namespace std;

int main(int argc, int *argv[]) {
	xpipe to_server,to_worker;
	Jobserver  jobs;
	
	jobs.set_send_pipe(to_worker);
	jobs.set_recv_pipe(to_server);
	jobs.start();
	
	return 0;
}
