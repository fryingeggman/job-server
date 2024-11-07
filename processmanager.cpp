#ifndef _MPROCESSMANAGER_CPP
#define _MPROCESSMANAGER_CPP

#include <iostream>
#include <list>
#include "processmanager.h"
using namespace std;

list<Worker> ProcessManager::m_workers;
int default_adjust_strategy(long jobs_count,ProcessManager &pm)
{
  long adj_num = jobs_count/10;

	if (adj_num > pm.get_maxprocnum()){
		adj_num = pm.get_maxprocnum();
	}
	else if (adj_num < pm.get_minprocnum()){
		adj_num = pm.get_minprocnum();
	}

	return adj_num;
}

ProcessManager::ProcessManager()
:adjust_proc_strategy(NULL),m_maxprocnum(10),m_minprocnum(1),m_jobs_count(0)
{
	signal(SIGCHLD,sig_child);
	signal(SIGTERM,sig_term);
}
ProcessManager::~ProcessManager()
{
}
void ProcessManager::init_num_process(int count)
{
	Worker *w=NULL;
	if (m_workers.empty()){
		for (int i = 0; i < count ; ++i){
			w = new Worker();
			if (w ==NULL){
				throw puts("create Worker failed,memory not enough");
			}
			m_workers.push_back(*w);
		}
	}
}

void ProcessManager::start()
{
	for (list<Worker>::iterator i=m_workers.begin();i!=m_workers.end();++i){
		i->start();
	}
}

void ProcessManager::sig_child(int sig)
{
	int recode;
	int pid=waitpid(-1,&recode,WNOHANG);
	
	for (list<Worker>::iterator i=m_workers.begin();i!=m_workers.end();++i){
		if (pid == i->pid()){
			i->set_status(false);
			break;
		}
	}

	signal(SIGCLD,sig_child);
}
void ProcessManager::sig_term(int sig)
{
	if (get_one_proc_by_status(true)){
		cout<<"some Worker process is still running"<<endl;
	}
	exit(0);
}
Worker * ProcessManager::get_one_proc_by_type(const string &type)
{
	for (list<Worker>::iterator i=m_workers.begin();i!=m_workers.end();++i){
		if (i->type() == type){
			return &(*i);
		}
	 }

	 return NULL;
}

Worker * ProcessManager::get_one_proc_by_status(bool status)
{
	for (list<Worker>::iterator i=m_workers.begin();i!=m_workers.end();++i){
        if (i->status() == status){
            return &(*i);
        }
    }
	return NULL;
}

void ProcessManager::adjust_proc_num()
{
	if (adjust_proc_strategy==NULL){
		adjust_proc_strategy = default_adjust_strategy;
	}
	int adj_num = adjust_proc_strategy(m_jobs_count,*this);
	
	Worker * w;
	
	while (cur_procnum() < adj_num){
		cout<<"+++++"<<endl;
		w=get_one_proc_by_status(false);
		w->start();
	}
//	while (cur_procnum() > adj_num){
	if (cur_procnum() > adj_num){
		cout<<"-----"<<endl;
		w=get_one_proc_by_status(true);
		w->stop();
	}
}
int ProcessManager::cur_procnum()
{
	int count=0;
	for(list<Worker>::iterator i=m_workers.begin();i!=m_workers.end();++i){
		if (i->status()){
			++count;
		}
	}

	return count;
}
#endif
