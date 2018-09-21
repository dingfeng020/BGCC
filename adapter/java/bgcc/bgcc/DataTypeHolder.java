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
 * @file     DataTypeHolder.java
 * @brief    
 * @author
 * @version  
 * @date     2012��08��30�� 18ʱ47��18��
 *  
 **/

package bgcc;

public final class DataTypeHolder {

    public DataTypeHolder() {
    }

    public DataTypeHolder(DataType value) {
        this.value = value;
    }

    public DataType value = DataType.getByValue(0);
}

