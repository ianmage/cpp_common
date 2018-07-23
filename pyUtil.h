#pragma once


void GetPyStack()
{
	PyThreadState* state = PyThreadState_Get();
	PyFrameObject* f = state->frame;
	while (f) {
		PyCodeObject* c = f->f_code;
		char *funcName = PyString_AsString(c->co_name);
		char *fileName = PyString_AsString(c->co_filename);
		int firstLn = c->co_firstlineco;
		f = f->f_back;
	}
}
