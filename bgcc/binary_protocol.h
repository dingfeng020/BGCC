/***********************************************************************
  * Copyright (c) 2012, Baidu Inc. All rights reserved.
  * 
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  * 
  *      license.txt
  *********************************************************************/

#ifndef _BGCC_BINARY_PROTOCOL_H_
#define _BGCC_BINARY_PROTOCOL_H_

#include "bgcc_common.h"
#include "protocol.h"
#include "nb_data_buffer.h"

namespace bgcc {

/*
 * HEAD + BODY
 * HEAD:
 * protocol(4) version(2)	protocoltype(1) reverd(1) logid(4) ticketid(4)	bodysize(4)
 * bgcP		   10			1				0					
 *
 * BODY:
 * processor_name		
 * msgType				2 byte
 * ticketid				4 byte
 * version				2 byte
 * function_name		string		
 * proxy_name			string
 *
 *
 * String	:	len+content
 * int32_t	:	4 byte	network order
 * */

extern const unsigned char bp_magic[];
extern const unsigned char bp_hb_hdr[];

#define HEAD_SIZE	20
#define LENGTH_SIZE	sizeof(int32_t)
#define MSGTYPE_LEN	2
#define TICKETID_LEN	4
#define VERSION_LEN		2
#define MAX_DEFAULT_LEN 1024


#define OFFSET_PTR(p, offset)	((p)?((char*)p+offset):NULL)
#define INT8(p) (*((int8_t*)((char*)p)))
#define UINT8(p) ((uint8_t)INT8(p))
#define INT16(p) (ntohs(*((int16_t*)((char*)p))))
#define INT32(p) (ntohl(*((int32_t*)((char*)p))))
#define INT64(p) (ntohll(*((int64_t*)((char*)p))))

#define ISHB(p) (0xff==UINT8(OFFSET_PTR(p, 7)))

#define BODY_LEN(pack_head) ((int32_t)ntohl(*(uint32_t*)(((char*)pack_head+16))))
#define	BODY_PTR(pack) ((char*)(pack)+(HEAD_SIZE))
#define BODY_LEN_PTR(pack) (BODY_PTR(pack)-LENGTH_SIZE)
#define PROCESSOR_NAME_LEN(pack_body) ((int32_t)ntohl(*(uint32_t*)pack_body))
#define PROCESSOR_NAME_PTR(pack_body) ((char*)pack_body+LENGTH_SIZE)
#define BODY_MINUS_PROCESSOR_PTR(pack_body)	\
	( PROCESSOR_NAME_PTR(pack_body)+ PROCESSOR_NAME_LEN(pack_body) )
#define BODY_MINUS_PROCESSOR_LEN(pack_body, body_len) \
	(  body_len- PROCESSOR_NAME_LEN(pack_body) - LENGTH_SIZE )

#define FUNC_NAME_OFFSET(pack_body) \
	(BODY_MINUS_PROCESSOR_PTR(pack_body)+MSGTYPE_LEN+TICKETID_LEN+VERSION_LEN)
#define FUNC_NAME_PTR(pack_body) \
	(FUNC_NAME_OFFSET(pack_body)+LENGTH_SIZE)
#define FUNC_NAME_LEN(pack_body) \
	((int32_t)ntohl(*(uint32_t*)(FUNC_NAME_OFFSET(pack_body))))

#define PROXY_NAME_OFFSET(pack_body) \
	(FUNC_NAME_PTR(pack_body)+FUNC_NAME_LEN(pack_body))
#define PROXY_NAME_PTR(pack_body)\
	(PROXY_NAME_OFFSET(pack_body)+LENGTH_SIZE)
#define PROXY_NAME_LEN(pack_body)\
	((int32_t)ntohl(*(uint32_t*)(PROXY_NAME_OFFSET(pack_body))))




    /**
     * @class BinaryProtocol 
     * @brief ʵ�ֶ�����Э�����л��뷴���л�
     *
     * �ṩ�������л��������л��Ķ����ƽӿڡ�
     */

    class BinaryProtocol : public IProtocol {
    public:
        /**
         * @brief   ���캯��
         * @param   transport �ײ�Ĵ��������ָ��
         */
        BinaryProtocol(TransportSharedPointer transport);
        /**
         * @brief   ����ֵ���л�
         * @param   value �����л��Ĳ���ֵ��
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeBool(const bool value);

        /**
         * @brief   8λ�������л�
         * @param   value �����л���8λ����ֵ��
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeByte(const int8_t value);

        /**
         * @brief   16λ�������л�
         * @param   value �����л���16λ����ֵ��
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeInt16(const int16_t value);

        /**
         * @brief   32λ�������л�
         * @param   value �����л���32λ����ֵ��
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeInt32(const int32_t value);

        /**
         * @brief   64λ�������л�
         * @param   value �����л���64λ����ֵ��
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeInt64(const int64_t value);

        /**
         * @brief   ���������л�
         * @param   value �����л��ĸ�������
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeFloat(const float value);

        /**
         * @brief   �ַ������л�
         * @param   value �����л����ַ�����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeString(const std::string& value);

        /**
         * @brief   �������������л�
         * @param   value �����л��Ķ��������ݡ�
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeBinary(const void* data, const int32_t size);

        /**
         * @brief   ��Ϣ���л���ʼ
         * @param   msgName ��Ϣ����
         * @param   msgType ��Ϣ����
         * @param   seqNO   ��Ϣ���к�
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeMessageBegin(
                const std::string& processor_name,
                const std::string& function_name,
                const MsgTypeID msg_type,
                const SequenceNOType seq_no);

        /**
         * @brief   ��Ϣ���л�����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeMessageEnd(bool tosend=true);

        /**
         * @brief   struct���л���ʼ
         * @param   name set����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeStructBegin(const std::string& name);

        /**
         * @brief   struct���л�����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeStructEnd();

        /**
         * @brief   �����л���ʼ
         * @param   name       ������
         * @param   fieldType �����ͱ�ʶ
         * @param   fieldId   ������
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeFieldBegin(
                const std::string& name,
                const DataTypeID fieldType,
                const FieldIDType fieldId);

        /**
         * @brief   �����л�����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeFieldEnd();

        /**
         * @brief   ���������л�, ���ڱ�ʶһϵ����Ľ���
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeFieldStop();

        /**
         * @brief   map���л���ʼ
         * @param   keyType �����ͱ�ʶ
         * @param   valueType ֵ���ͱ�ʶ
         * @param   size Ԫ�ظ���
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeMapBegin(
                const DataTypeID keyType,
                const DataTypeID valueType,
                const int32_t size);

        /**
         * @brief   map���л�����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeMapEnd();

        /**
         * @brief   list���л���ʼ
         * @param   elemType Ԫ�����ͱ�ʶ
         * @param   size Ԫ�ظ���
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeListBegin(
                const DataTypeID elemType,
                const int32_t size);

        /**
         * @brief   list���л�����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeListEnd();

        /**
         * @brief   set���л���ʼ
         * @param   elemType Ԫ�����ͱ�ʶ
         * @param   size Ԫ�ظ���
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeSetBegin(
                const DataTypeID elemType,
                const int32_t size);

        /**
         * @brief   set���л�����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t writeSetEnd();

        /**
         * @brief   ����ֵ�����л�
         * @param   value �����л���õ��Ĳ���ֵ
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readBool(char *request, int32_t request_len, bool& value);

        /**
         * @brief   8λ���������л�
         * @param   value �����л���õ���8λ����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readByte(char *request, int32_t request_len, int8_t& value);

        /**
         * @brief   16λ���������л�
         * @param   value �����л���õ���16λ����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readInt16(char *request, int32_t request_len, int16_t& value);

        /**
         * @brief   32λ���������л�
         * @param   value �����л���õ���32λ����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readInt32(char *request, int32_t request_len, int32_t& value);

        /**
         * @brief   64λ���������л�
         * @param   value �����л���õ���64λ����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readInt64(char *request, int32_t request_len, int64_t& value);

        /**
         * @brief   �����������л�
         * @param   value �����л���õ��ĸ�����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readFloat(char *request, int32_t request_len, float& value);

        /**
         * @brief   �ַ��������л�
         * @param   value �����л���õ����ַ���
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readString(char *request, int32_t request_len, std::string& value);

        /**
         * @brief   ���������ݷ����л�
         * @param   value �����л���õ��Ķ���������
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readBinary(char *request, int32_t request_len, std::string& value);

        /**
         * @brief   set�����л���ʼ
         * @param   elemType �����л���õ���setԪ�����ͱ�ʶ
         * @param   size �����л���õ���setԪ�ظ���
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readSetBegin(char *request, int32_t request_len, DataTypeID& elemType, int32_t& size);

        /**
         * @brief   set�����л�����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readSetEnd();

        /**
         * @brief   list�����л���ʼ
         * @param   elemType �����л���õ���listԪ�����ͱ�ʶ
         * @param   size �����л���õ���listԪ�ظ���
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readListBegin(char *request, int32_t request_len, DataTypeID& elemType, int32_t& size);

        /**
         * @brief   list�����л�����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readListEnd();

        /**
         * @brief   map�����л���ʼ
         * @param   keyType �����л���õ���map�����ͱ�ʶ
         * @param   valueType �����л���õ���mapֵ���ͱ�ʶ
         * @param   size �����к�õ���Ԫ�ظ���
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readMapBegin(
				char *request,
                int32_t request_len, 
                DataTypeID& keyType,
                DataTypeID& valueType,
                int32_t& size);

        /**
         * @brief   map�����л�����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readMapEnd();

        /**
         * @brief   struct�����л���ʼ
         * @param   name �����л���õ���struct����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readStructBegin(char *request, int32_t request_len, std::string& name);

        /**
         * @brief   struct�����л�����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readStructEnd();

        /**
         * @brief   ��Ϣ�����л���ʼ
         * @param   msgName �����л���õ�����Ϣ����
         * @param   msgType �����л���õ�����Ϣ����
         * @param   seqNO �����л��õ�����Ϣ���к�
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readMessageBegin(
				char **request,
                int32_t &request_len, 
                std::string& msgName,
                MsgTypeID& msgType,
                SequenceNOType& seqNO,
				ReadItem *pItem=NULL);

        /**
         * @brief   ��Ϣ�����л�����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readMessageEnd();

        /**
         * @brief   �����л���ʼ
         * @param   name �����л���õ���������
         * @param   field_type �����л���õ��������ͱ�ʶ
         * @param   field_id ������
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readFieldBegin(
				char *request,
                int32_t request_len, 
                std::string& name,
                DataTypeID& fieldType,
                FieldIDType& fieldID);

        /**
         * @brief   �����л�����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t readFieldEnd();

        /**
         * @brief   ���ñ�Э������Ӧ�ĵײ㴫�������ָ�����
         * @param   transport �����õĴ��������ָ�����
         * @return  �ɹ�ʱ����0������ʱ���ش����롣
         */
        virtual int32_t setTransport(TransportSharedPointer transport);

        /**
         * @brief   ��ȡ��Э������Ӧ�ĵײ㴫�������ָ�����
         * @return  ���������ָ�����
         */
        virtual TransportSharedPointer getTransport();

        int32_t getDataCopy(void** ppdata, int32_t& size);
    
        NBDataBuffer* get_data_buffer() {
            return &_data;
        }
    private:
        /** �ײ�Ĵ�����������ָ�� */
        TransportSharedPointer _transport;
        NBDataBuffer _data;

	private:
		int32_t readBasic(char *_dstbuf, int32_t dstbuf_len, const char *srcbuf, int32_t srcbuf_len);
    };
}

#endif
