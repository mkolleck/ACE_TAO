
#include "Session_Task.h"
#include "Session.h"

Session_Task::Session_Task (Session *session)
  : session_ (session)
{
}

int
Session_Task::svc ()
{
  return this->session_->svc ();
}
