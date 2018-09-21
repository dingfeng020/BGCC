/***********************************************************************
  * Copyright (c) 2012, Baidu Inc. All rights reserved.
  * 
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  * 
  *      license.txt
  *********************************************************************/

#ifndef _BGCC2_TIME_UTIL_H_
#define _BGCC2_TIME_UTIL_H_

#include <string>
#include "bgcc_common.h"

namespace bgcc {

    /**
     * @brief 时间实用工具类
     * @see
     * @note
     * @author
     * @date    2012年05月30日 21时11分15秒
     */

#ifdef _WIN32
    struct timezone 
    {
        int  tz_minuteswest; /* minutes W of Greenwich */
        int  tz_dsttime;     /* type of dst correction */
    };

	//int gettimeofday(struct ::timeval *tv, struct timezone *tz);
#endif

    class TimeUtil {
    public:
        /**
         * @brief get_timestamp_s 获取时间戳（秒）
         *
         * @return 返回从Epoch所经过的秒数
         * @see
         * @note
         * @author
         * @date    2012年05月30日 21时11分25秒
         */
        static uint64_t get_timestamp_s();

        /**
         * @brief get_timestamp_ms 获取时间戳（毫秒）
         *
         * @return 返回从Epoch所经过的微秒数
         * @see
         * @note
         * @author
         * @date    2012年05月30日 21时12分14秒
         */
        static uint64_t get_timestamp_ms();
        
        /**
         * @brief 获取微秒级时间戳
         *
         * @return  uint64_t 
         * @retval   
         * @see 
         * @note 
         * @author zhangyue
         * @date 2012/12/24 16:38:45
        **/
        static uint64_t get_timestamp_us();

        /**
         * @brief safe_sleep_s 支持中断的sleep（秒）
         *
         * @param second 睡眠的秒数
         * @see
         * @note
         * @author
         * @date    2012年05月30日 21时12分42秒
         */
        static void safe_sleep_s(uint32_t second);

        /**
         * @brief safe_sleep_ms 支持中断的sleep（毫秒）
         *
         * @param millisecond 睡眠的毫秒数
         * @see
         * @note
         * @author
         * @date    2012年05月30日 21时13分05秒
         */
        static void safe_sleep_ms(uint32_t millisecond);

        /**
         * @brief format_datetime_str 将时间戳格式化
         *
         * @param millisecond 从Epoch所经过的毫秒数
         *
         * @return 时间戳字符串
         * @see
         * @note
         * @author
         * @date    2012年05月30日 21时13分53秒
         */
        static std::string format_datetime_str(uint64_t millisecond);

#ifndef _WIN32
//        struct ::timespec;
        /**
         * @brief get_abs_timespec 获取从当前时间后 milliSeconds 毫秒后的绝对时间
         *
         * @param ts 存放绝对时间
         * @param millisecond 当前后的毫秒数
         *
         * @return 成功返回0
         * @see
         * @note
         * @author
         * @date    2012年05月30日 21时14分47秒
         */
        static int32_t get_abs_timespec(struct timespec* ts, int32_t millisecond);
#endif

        /**
         * @brief strftimeval 将struct timeval转换为字符串形式，格式为"YYYY-MM-DD HH:mm::SS.xxx"
         *
         * @param buffer [out] 接收缓冲区。推荐缓冲区大小为24个字节。
         * @param buflen 缓冲区大小
         * @param tv 待转换的struct timeval指针
         *
         * @return 返回写入缓冲区的字符个数（不含\0）；否则返回-1
         * @see
         * @note
         * @author
         * @date    2012年05月22日 16时50分14秒
         */
        static int32_t strftimeval(char* buffer, int32_t buflen, const struct timeval* tv);

        /**
         * @brief get_date 获取日期串 "YYYYMMDD"
         *
         * @return 日期串
         * @see
         * @note
         * @author
         * @date    2012年06月12日 17时23分19秒
         */
        static std::string get_date();

        /**
         * @brief get_time 获取时间串 "HHmmSS.xxx"
         *
         * @return 
         * @see
         * @note
         * @author
         * @date    2012年06月12日 17时23分56秒
         */
        static std::string get_time();

        /**
         * @brief 获取当前星期几
         *
         * @return  int32_t 
         * @retval   
         * @see 
         * @note 
         * @author zhangyue
         * @date 2012/12/24 16:20:08
        **/
        static int32_t get_day();

        /**
         * @brief 获取指定日期的星期几
         *
         * @param [in/out] time   : time_t
         * @return  int32_t 
         * @retval   
         * @see 
         * @note 
         * @author zhangyue
         * @date 2012/12/24 16:20:11
        **/
        static int32_t get_day( time_t time );

        /**
         * @brief 格式化当前时间，默认格式为【%Y%m%d-%H:%M:%S】
         *
         * @param [in/out] fmt   : const char*
         * @return  std::string 
         * @retval   
         * @see 
         * @note 
         * @author zhangyue
         * @date 2012/12/24 16:20:18
        **/
        static std::string format_time(const char * fmt = NULL);

        /**
         * @brief 格式化指定时间，默认格式为【%Y%m%d-%H:%M:%S】
         *
         * @param [in/out] time   : time_t
         * @param [in/out] fmt   : const char*
         * @return  std::string 
         * @retval   
         * @see 
         * @note 
         * @author zhangyue
         * @date 2012/12/24 16:20:28
        **/
        static std::string format_time(time_t time, const char * fmt = NULL);

        /**
         * @brief 格式化指定时间，默认格式为【%Y%m%d-%H:%M:%S】
         *
         * @param [in/out] time   : const struct timeval*
         * @param [in/out] fmt   : const char*
         * @return  std::string 
         * @retval   
         * @see 
         * @note 
         * @author zhangyue
         * @date 2012/12/24 16:20:31
        **/
        static std::string format_time(const struct timeval* tv, const char * fmt = NULL);
		 
		/**
         * @brief 格式化指定时间，默认格式为【%Y%m%d-%H:%M:%S】
         *
         * @param [in/out] time   : const struct timeval*
         * @param [in/out] fmt   : const char*
         * @return  std::string 
         * @retval   
         * @see 
         * @note 
         * @author zhangyue
         * @date 2012/12/24 16:20:31
        **/
		static int32_t gettimeofday(struct ::timeval *tv, struct timezone *tz);

#ifdef _WIN32
    private:
		/*__declspec(thread)*/ static FILETIME _ft;             /**< 标准时间    */
        /*__declspec(thread)*/ static LARGE_INTEGER _pform;     /**< 标准时间戳  */
#endif
    }; // end of class TimeUtil
}

#endif // _BGCC2_TIME_UTIL_H_

