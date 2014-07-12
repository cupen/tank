/*
 * log.h
 *
 *  Created on: 2014年7月12日
 *      Author: cupen
 */

#ifndef LOG_H_
#define LOG_H_




#ifdef __cplusplus
extern "C"
{
#endif

	void set_log_level();
	void log_debug();
	void log_info();
	void log_error();


#ifdef __cplusplus
extern "C"
}
#endif


#endif /* LOG_H_ */
