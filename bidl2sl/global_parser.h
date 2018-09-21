/***********************************************************************
  * Copyright (c) 2012, Baidu Inc. All rights reserved.
  * 
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  * 
  *      license.txt
  *********************************************************************/

/**
 * @file     global_parser.h
 * @brief    
 * @author
 * @version  
 * @date     2012��08��16�� 14ʱ40��22��
 *  
 **/
#ifndef _BIDL2SL_GLOBAL_PARSER_H_
#define _BIDL2SL_GLOBAL_PARSER_H_

#include <limits.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <stdint.h>

/**
 * @brief ͳһ�����������ɸ�bidl�ļ�
 * @see
 * @note
 * @author
 * @date    2012��08��16�� 14ʱ40��55��
 */
class GlobalParser {
public:
    GlobalParser();
    void add_bidl(const std::string& bidl);
    void parse();

    bool is_debuged() const {
        return _debuged;
    }

    void set_debuged() {
        _debuged = true;
    }

    bool is_lang_setted() const {
        return _lang_setted;
    }

    void set_language(const std::string& lang) {
        _language = lang;

        if (!is_outdir_setted()) {
            _outdir = "output-" + _language + "/";
        }
        _lang_setted = true;
    }

    std::string get_language() const {
        return _language;
    }

    bool is_outdir_setted() const {
        return _outdir_setted;
    }

    void set_outdir(const std::string& outdir) {
        if (outdir[outdir.length()-1] != '/') {
            _outdir = outdir + "/";
        }
        else {
            _outdir = outdir;
        }
        _outdir_setted = true;
    }

    std::string get_outdir() const {
        return _outdir;
    }

    void add_bidl_include_dir(const std::string& dir);

    std::vector<std::string> get_bidl_include_dirs() const {
        return _bidl_incldue_dirs;
    }

    bool is_bidl_exist_in_bidl_include_dirs(const std::string& bidl, std::string& dir);

    static bool is_file_exist(const std::string& full_name);
    static bool is_dir_exist(const std::string& dir);
    static std::string get_desent() {
        return "    ";
    }

    std::string get_tmp_var() {
        static int32_t i = 0;
        static const char* prefix = "var";
        std::stringstream ss;

        ss << prefix << ++i;

        if (i >= INT_MAX) {
            i = 0;
        }
        return ss.str();
    }
private:
    bool _debuged;
    bool _lang_setted;
    std::string _language;
    bool _outdir_setted;
    std::string _outdir;
    std::vector<std::string> _bidl_incldue_dirs;    /** end by '/' */
    std::vector<std::string> _bidls;

};
#endif // _BIDL2SL_GLOBAL_PARSER_H_

