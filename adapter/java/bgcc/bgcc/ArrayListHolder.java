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
 * @file     ArrayListHolder.java
 * @brief    byte���͵�Holder��,���ڴ���out ,all���͵�byte���� 
 * @author
 * @version  
 * @date     2012��08��30�� 16ʱ04��09��
 *  
 **/

package bgcc;

public final class ArrayListHolder {

    public ArrayListHolder() {
    }

    public ArrayListHolder(java.util.ArrayList value) {
        this.value = value;
    }

    public java.util.ArrayList value = null;
}

