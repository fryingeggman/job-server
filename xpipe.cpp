#ifndef __XPIPECPP__
#define __XPIPECPP__

#include "xpipe.h"

xpipe::xpipe()
:m_readable(true),m_writeable(true),m_buf(NULL)
{
  int success=pipe(m_fd);
	if(success<0)
	{
		throw puts("create pipe failed!");
	}
	//检测系统设置的管道限制大小
	m_bufsize=fpathconf(m_fd[0],_PC_PIPE_BUF);
	
}
xpipe::~xpipe()
{
	if(m_readable)
		close(m_fd[0]);
	if(m_writeable)
		close(m_fd[1]);
	if(m_buf!=NULL)
		delete m_buf;
}
ssize_t xpipe::send(void *buf, size_t n)
{
	return write(m_fd[1], buf, n);
}
ssize_t xpipe::recv(void *buf, size_t nbytes)
{
	return read(m_fd[0], buf, nbytes);
}
ssize_t xpipe::send(const string &content)
{
	return write(m_fd[1],content.c_str(),content.length());
}
ssize_t xpipe::recv(string &content)
{
	if (m_buf==NULL)
	{//lazy run
		m_buf=new char[m_bufsize];
		if (m_buf==NULL)
		{
			throw puts("memory not enough!");
		}
	}
	memset(m_buf,0,m_bufsize);
	int n = read(m_fd[0],m_buf,m_bufsize);
	content=string(m_buf);
	return n;
}
//返回当前管道所扮演到角色
string xpipe::role() const
{
	if (m_writeable&&m_readable)
	{
		return "sender and receiver";
	}
	if (m_writeable)
	{
		return "sender";
	}
	if (m_readable)
	{
		return "receiver";
	}

	return "none";
	
}
/*关闭读端口*/
void xpipe::DisReadable()
{
	if(m_readable)
	{
		close(m_fd[0]);
		m_readable=false;
	}	
}
/*关闭写端口*/
void xpipe::DisWriteable()
{
	if (m_writeable)
	{
		close(m_fd[1]);
		m_writeable=false;
	}
		
}
/*如果输入大于0：调整缓存区大小，并返回调整后缓存区大小
  如果输入小于等于0，则不设置，只返回缓存区大小
  缓存区大小构造时默认设置为系统对管道的限制大小
  默认参数为0
 */
long xpipe::Bufsize(long newbufsize)
{
	//大于0才设置
	if (newbufsize>0)
	{
		m_bufsize=newbufsize;
		delete m_buf;
		//重新申请缓存区
		m_buf=new char[m_bufsize];
		if (m_buf==NULL)
		{
			throw puts("memory not enough!");
		}
	}
	
	return m_bufsize;
}
#endif
