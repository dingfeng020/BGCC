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
 * @file     MessageTypeHolder.java
 * @brief    
 * @author
 * @version  
 * @date     2012��08��30�� 18ʱ59��57��
 *  
 **/

package bgcc;

public final class MessageTypeHolder {
    public MessageTypeHolder() {
    }

    public MessageTypeHolder(MessageType value) {
        this.value = value;
    }

    public MessageType value = MessageType.getByValue(0);
}

