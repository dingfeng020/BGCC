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
 * @file     ExceptionTypeHolder.java
 * @brief    
 * @author
 * @version  
 * @date     2012��08��30�� 18ʱ55��12��
 *  
 **/

package bgcc;

public final class ExceptionTypeHolder {

    public ExceptionTypeHolder() {
    }

    public ExceptionTypeHolder(ExceptionType value) {
        this.value = value;
    }

    public ExceptionType value = ExceptionType.getByValue(0);
}

