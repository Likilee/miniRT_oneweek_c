#include "control.h"

void	cntl_default_mode_on(t_cntl *cntl)
{
	cntl->mode = DEFM;
	console_msg_welcome();
}
