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
 * @file     Holder.java
 * @brief    ��ͨHolder�࣬����bgcc in/all ���͵Ĳ����Ĵ���
 * @author
 * @version  
 * @date     2012��08��30�� 16ʱ11��01��
 *  
 **/

package bgcc;

public class Holder<T> {

    public Holder() {
    }

    public Holder(T value) {
        this.value = value;
    }

    public T value;
}

