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
 * @file     LinkedListHolder.java
 * @brief    LinkedList��holder������all, out����
 * @author
 * @version  
 * @date     2012��08��30�� 16ʱ13��00��
 *  
 **/

package bgcc;

public final class LinkedListHolder {

    public LinkedListHolder() {
    }

    public LinkedListHolder(java.util.LinkedList value) {
        this.value = value;
    }

    public java.util.LinkedList value = null;
}

