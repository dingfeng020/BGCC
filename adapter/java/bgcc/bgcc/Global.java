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
 * @file     Global.java
 * @brief    
 * @author
 * @version  
 * @date     2012��09��01�� 13ʱ04��38��
 *  
 **/

package bgcc;

public class Global {
    private Logger _logger = null;

    public Logger getLogger() {
        return _logger;
    }

    public void setLogger(Logger logger) {
        _logger = logger;
    }

    private Global() {
    }

    private static Global _instance = new Global();

    public static Global instance() {
        return _instance;
    }
}

