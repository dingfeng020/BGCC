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
 * @file     ListHolder.java
 * @brief    LinkedList��holder������all, out����
 * @author
 * @version  
 * @date     2012��08��30�� 16ʱ26��35��
 *  
 **/

package bgcc;

public final class ListHolder {

    public ListHolder() {
    }

    public ListHolder(java.util.List value) {
        this.value = value;
    }

    public java.util.List value = null;
}

