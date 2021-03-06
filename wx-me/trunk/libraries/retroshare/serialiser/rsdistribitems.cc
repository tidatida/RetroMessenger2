
/*
 * libretroshare/src/serialiser: rsforumitems.cc
 *
 * RetroShare Serialiser.
 *
 * Copyright 2007-2008 by Robert Fernie.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License Version 2 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA.
 *
 * Please report all bugs and problems to "retroshare@lunamutt.com".
 *
 */

#include "serialiser/rsdistribitems.h"

#include "serialiser/rsbaseserial.h"
#include "serialiser/rstlvbase.h"

#define RSSERIAL_DEBUG 1
#include <iostream>

/*************************************************************************/

void 	RsDistribMsg::clear()
{
	grpId.clear();
	parentId.clear();
	threadId.clear();
	timestamp = 0;


	msgId.clear();
	publishSignature.TlvClear();
	personalSignature.TlvClear();
}

std::ostream &RsDistribMsg::print(std::ostream &out, uint16_t indent)
{
        printRsItemBase(out, "RsDistribMsg", indent);
	uint16_t int_Indent = indent + 2;
        printIndent(out, int_Indent);
        out << "grpId: " << grpId << std::endl;
        printIndent(out, int_Indent);
        out << "parentId: " << parentId << std::endl;
        printIndent(out, int_Indent);
        out << "threadId: " << threadId << std::endl;

        printIndent(out, int_Indent);
        out << "timestamp:  " << timestamp  << std::endl;

        printIndent(out, int_Indent);
        out << "<<<<<<<< Not Serialised >>>>>>>>" << std::endl;

        printIndent(out, int_Indent);
        out << "msgId: " << msgId << std::endl;
	publishSignature.print(out, int_Indent);
	personalSignature.print(out, int_Indent);

        out << "<<<<<<<< Not Serialised >>>>>>>>" << std::endl;

        printRsItemEnd(out, "RsDistribMsg", indent);
        return out;
}


void 	RsDistribSignedMsg::clear()
{
	grpId.clear();
	msgId.clear();
	flags = 0;
	timestamp = 0;
	packet.TlvClear();
	publishSignature.TlvClear();
	personalSignature.TlvClear();

	return;
}

std::ostream &RsDistribSignedMsg::print(std::ostream &out, uint16_t indent)
{
        printRsItemBase(out, "RsDistribSignedMsg", indent);
	uint16_t int_Indent = indent + 2;

        printIndent(out, int_Indent);
        out << "grpId: " << grpId << std::endl;
        printIndent(out, int_Indent);
        out << "msgId: " << msgId << std::endl;
        printIndent(out, int_Indent);
        out << "flags: " << flags << std::endl;
        printIndent(out, int_Indent);
        out << "timestamp: " << timestamp << std::endl;
	packet.print(out, 10);
	publishSignature.print(out, 10);
	personalSignature.print(out, 10);

        printRsItemEnd(out, "RsDistribSignedMsg", indent);
        return out;
}

/*************************************************************************/

void 	RsDistribGrp::clear()
{
	grpId.clear();
	timestamp = 0;
	grpFlags = 0;
	grpName.clear();
	grpDesc.clear();
	grpCategory.clear();

	grpControlFlags = 0;
	grpControlList.TlvClear();

	grpPixmap.TlvClear();

	adminKey.TlvClear();
	publishKeys.TlvClear();

	adminSignature.TlvClear();
}

std::ostream &RsDistribGrp::print(std::ostream &out, uint16_t indent)
{
        printRsItemBase(out, "RsDistribGrp", indent);
	uint16_t int_Indent = indent + 2;
        printIndent(out, int_Indent);
        out << "grpId: " << grpId << std::endl;
        printIndent(out, int_Indent);
        out << "timestamp: " << timestamp << std::endl;
        printIndent(out, int_Indent);
        out << "grpFlags: " << grpFlags << std::endl;

        printIndent(out, int_Indent);

	std::string cnv_name(grpName.begin(), grpName.end());
        out << "grpName:  " << cnv_name  << std::endl;

        printIndent(out, int_Indent);

	std::string cnv_desc(grpDesc.begin(), grpDesc.end());
        out << "grpDesc:  " << cnv_desc  << std::endl;

        printIndent(out, int_Indent);
	std::string cnv_category(grpCategory.begin(), grpCategory.end());
        out << "grpCategory: " << cnv_category << std::endl;

        printIndent(out, int_Indent);
        out << "grpControlFlags: " << grpControlFlags << std::endl;

	grpControlList.print(out, int_Indent);

	grpPixmap.print(out, int_Indent);

	adminKey.print(out, int_Indent);
	publishKeys.print(out, int_Indent);
	adminSignature.print(out, int_Indent);

        printRsItemEnd(out, "RsDistribGrp", indent);
        return out;
}

/*************************************************************************/

void 	RsDistribGrpKey::clear()
{
	grpId.clear();
	key.TlvClear();
}

std::ostream &RsDistribGrpKey::print(std::ostream &out, uint16_t indent)
{
        printRsItemBase(out, "RsDistribGrpKey", indent);
	uint16_t int_Indent = indent + 2;
        printIndent(out, int_Indent);
        out << "grpId: " << grpId << std::endl;

	key.print(out, int_Indent);

        printRsItemEnd(out, "RsDistribGrpKey", indent);
        return out;
}

/*************************************************************************/
/*************************************************************************/

uint32_t    RsDistribSerialiser::sizeGrp(RsDistribGrp *item)
{
	uint32_t s = 8; /* header */
	/* RsDistribMsg stuff */
	s += GetTlvStringSize(item->grpId);
	s += 4; /* timestamp */
	s += 4; /* grpFlags  */
	s += GetTlvWideStringSize(item->grpName);
	s += GetTlvWideStringSize(item->grpDesc);
	s += GetTlvWideStringSize(item->grpCategory);

	s += 4; /* grpControlFlags  */
	s += item->grpControlList.TlvSize();

	s += item->grpPixmap.TlvSize();

	s += item->adminKey.TlvSize();
	s += item->publishKeys.TlvSize();
	s += item->adminSignature.TlvSize();

	return s;
}

/* serialise the data to the buffer */
bool     RsDistribSerialiser::serialiseGrp(RsDistribGrp *item, void *data, uint32_t *pktsize)
{
	uint32_t tlvsize = sizeGrp(item);
	uint32_t offset = 0;

	if (*pktsize < tlvsize)
		return false; /* not enough space */

	*pktsize = tlvsize;

	bool ok = true;

	ok &= setRsItemHeader(data, tlvsize, item->PacketId(), tlvsize);

	/* skip the header */
	offset += 8;

	/* RsDistribGrp */
	ok &= SetTlvString(data, tlvsize, &offset, TLV_TYPE_STR_GROUPID, item->grpId);
	ok &= setRawUInt32(data, tlvsize, &offset, item->timestamp);
	ok &= setRawUInt32(data, tlvsize, &offset, item->grpFlags);

	ok &= SetTlvWideString(data, tlvsize, &offset, TLV_TYPE_WSTR_NAME, item->grpName);
	ok &= SetTlvWideString(data, tlvsize, &offset, TLV_TYPE_WSTR_COMMENT, item->grpDesc);
	ok &= SetTlvWideString(data, tlvsize, &offset, TLV_TYPE_WSTR_CATEGORY, item->grpCategory);

	ok &= setRawUInt32(data, tlvsize, &offset, item->grpControlFlags);
	ok &= item->grpControlList.SetTlv(data, tlvsize, &offset);

	ok &= item->grpPixmap.SetTlv(data, tlvsize, &offset);

	ok &= item->adminKey.SetTlv(data, tlvsize, &offset);
	ok &= item->publishKeys.SetTlv(data, tlvsize, &offset);
	ok &= item->adminSignature.SetTlv(data, tlvsize, &offset);

	if (offset != tlvsize)
	{
		ok = false;
		std::cerr << "RsDistribSerialiser::serialiseGrp() Size Error! " << std::endl;
	}

	return ok;
}


RsDistribGrp *RsDistribSerialiser::deserialiseGrp(void *data, uint32_t *pktsize)
{
	/* get the type and size */
	uint32_t rstype = getRsItemId(data);
	uint32_t rssize = getRsItemSize(data);

	uint32_t offset = 0;


	if ((RS_PKT_VERSION_SERVICE != getRsItemVersion(rstype)) ||
		(RS_SERVICE_TYPE_DISTRIB != getRsItemService(rstype)) ||
		(RS_PKT_SUBTYPE_DISTRIB_GRP != getRsItemSubType(rstype)))
	{
		return NULL; /* wrong type */
	}

	if (*pktsize < rssize)    /* check size */
		return NULL; /* not enough data */

	/* set the packet length */
	*pktsize = rssize;

	bool ok = true;

	/* ready to load */
	RsDistribGrp *item = new RsDistribGrp();
	item->clear();

	/* skip the header */
	offset += 8;

	/* RsDistribGrp */
	ok &= GetTlvString(data, rssize, &offset, TLV_TYPE_STR_GROUPID, item->grpId);
	ok &= getRawUInt32(data, rssize, &offset, &(item->timestamp));
	ok &= getRawUInt32(data, rssize, &offset, &(item->grpFlags));

	ok &= GetTlvWideString(data, rssize, &offset, TLV_TYPE_WSTR_NAME, item->grpName);
	ok &= GetTlvWideString(data, rssize, &offset, TLV_TYPE_WSTR_COMMENT, item->grpDesc);
	ok &= GetTlvWideString(data, rssize, &offset, TLV_TYPE_WSTR_CATEGORY, item->grpCategory);

	ok &= getRawUInt32(data, rssize, &offset, &(item->grpControlFlags));
	ok &= item->grpControlList.GetTlv(data, rssize, &offset);

	ok &= item->grpPixmap.GetTlv(data, rssize, &offset);

	ok &= item->adminKey.GetTlv(data, rssize, &offset);
	ok &= item->publishKeys.GetTlv(data, rssize, &offset);
	ok &= item->adminSignature.GetTlv(data, rssize, &offset);

	if (offset != rssize)
	{
		/* error */
		delete item;
		return NULL;
	}

	if (!ok)
	{
		delete item;
		return NULL;
	}

	return item;
}

/*************************************************************************/

uint32_t    RsDistribSerialiser::sizeGrpKey(RsDistribGrpKey *item)
{
	uint32_t s = 8; /* header */
	s += GetTlvStringSize(item->grpId);
	s += item->key.TlvSize();

	return s;
}

/* serialise the data to the buffer */
bool     RsDistribSerialiser::serialiseGrpKey(RsDistribGrpKey *item, void *data, uint32_t *pktsize)
{
	uint32_t tlvsize = sizeGrpKey(item);
	uint32_t offset = 0;

	if (*pktsize < tlvsize)
		return false; /* not enough space */

	*pktsize = tlvsize;

	bool ok = true;

	ok &= setRsItemHeader(data, tlvsize, item->PacketId(), tlvsize);

	/* skip the header */
	offset += 8;

	/* RsDistribGrp */
	ok &= SetTlvString(data, tlvsize, &offset, TLV_TYPE_STR_GROUPID, item->grpId);

	ok &= item->key.SetTlv(data, tlvsize, &offset);

	if (offset != tlvsize)
	{
		ok = false;
		std::cerr << "RsDistribSerialiser::serialiseGrpKey() Size Error! " << std::endl;
	}

	return ok;
}


RsDistribGrpKey *RsDistribSerialiser::deserialiseGrpKey(void *data, uint32_t *pktsize)
{
	/* get the type and size */
	uint32_t rstype = getRsItemId(data);
	uint32_t rssize = getRsItemSize(data);

	uint32_t offset = 0;


	if ((RS_PKT_VERSION_SERVICE != getRsItemVersion(rstype)) ||
		(RS_SERVICE_TYPE_DISTRIB != getRsItemService(rstype)) ||
		(RS_PKT_SUBTYPE_DISTRIB_GRP_KEY != getRsItemSubType(rstype)))
	{
		return NULL; /* wrong type */
	}

	if (*pktsize < rssize)    /* check size */
		return NULL; /* not enough data */

	/* set the packet length */
	*pktsize = rssize;

	bool ok = true;

	/* ready to load */
	RsDistribGrpKey *item = new RsDistribGrpKey();
	item->clear();

	/* skip the header */
	offset += 8;

	/* RsDistribGrp */
	ok &= GetTlvString(data, rssize, &offset, TLV_TYPE_STR_GROUPID, item->grpId);
	ok &= item->key.GetTlv(data, rssize, &offset);

	if (offset != rssize)
	{
		/* error */
		delete item;
		return NULL;
	}

	if (!ok)
	{
		delete item;
		return NULL;
	}

	return item;
}

/*************************************************************************/

uint32_t    RsDistribSerialiser::sizeSignedMsg(RsDistribSignedMsg *item)
{
	uint32_t s = 8; /* header */
	/* RsDistribSignedMsg stuff */
	s += GetTlvStringSize(item->grpId);
	s += GetTlvStringSize(item->msgId);
	s += 4; /* flags */
	s += 4; /* timestamp */
	s += item->packet.TlvSize();
	s += item->publishSignature.TlvSize();
	s += item->personalSignature.TlvSize();

	return s;
}

/* serialise the data to the buffer */
bool     RsDistribSerialiser::serialiseSignedMsg(RsDistribSignedMsg *item, void *data, uint32_t *pktsize)
{
	uint32_t tlvsize = sizeSignedMsg(item);
	uint32_t offset = 0;

	if (*pktsize < tlvsize)
		return false; /* not enough space */

	*pktsize = tlvsize;

	bool ok = true;

	ok &= setRsItemHeader(data, tlvsize, item->PacketId(), tlvsize);

	/* skip the header */
	offset += 8;

	/* RsDistribSignedMsg */
	ok &= SetTlvString(data, tlvsize, &offset, TLV_TYPE_STR_GROUPID, item->grpId);
	ok &= SetTlvString(data, tlvsize, &offset, TLV_TYPE_STR_MSGID, item->msgId);

	ok &= setRawUInt32(data, tlvsize, &offset, item->flags);
	ok &= setRawUInt32(data, tlvsize, &offset, item->timestamp);

	ok &= item->packet.SetTlv(data, tlvsize, &offset);

	ok &= item->publishSignature.SetTlv(data, tlvsize, &offset);
	ok &= item->personalSignature.SetTlv(data, tlvsize, &offset);

	if (offset != tlvsize)
	{
		ok = false;
		std::cerr << "RsDistribSerialiser::serialiseSignedMsg() Size Error! " << std::endl;
	}

	return ok;
}


RsDistribSignedMsg *RsDistribSerialiser::deserialiseSignedMsg(void *data, uint32_t *pktsize)
{
	/* get the type and size */
	uint32_t rstype = getRsItemId(data);
	uint32_t rssize = getRsItemSize(data);

	uint32_t offset = 0;


	if ((RS_PKT_VERSION_SERVICE != getRsItemVersion(rstype)) ||
		(RS_SERVICE_TYPE_DISTRIB != getRsItemService(rstype)) ||
		(RS_PKT_SUBTYPE_DISTRIB_SIGNED_MSG != getRsItemSubType(rstype)))
	{
		return NULL; /* wrong type */
	}

	if (*pktsize < rssize)    /* check size */
		return NULL; /* not enough data */

	/* set the packet length */
	*pktsize = rssize;

	bool ok = true;

	/* ready to load */
	RsDistribSignedMsg *item = new RsDistribSignedMsg();
	item->clear();

	/* skip the header */
	offset += 8;

	/* RsDistribGrp */
	ok &= GetTlvString(data, rssize, &offset, TLV_TYPE_STR_GROUPID, item->grpId);
	ok &= GetTlvString(data, rssize, &offset, TLV_TYPE_STR_MSGID, item->msgId);
	ok &= getRawUInt32(data, rssize, &offset, &(item->flags));
	ok &= getRawUInt32(data, rssize, &offset, &(item->timestamp));

	ok &= item->packet.GetTlv(data, rssize, &offset);

	ok &= item->publishSignature.GetTlv(data, rssize, &offset);
	ok &= item->personalSignature.GetTlv(data, rssize, &offset);

	if (offset != rssize)
	{
		/* error */
		delete item;
		return NULL;
	}

	if (!ok)
	{
		delete item;
		return NULL;
	}

	return item;
}





uint32_t    RsDistribSerialiser::size(RsItem *i)
{
	RsDistribGrp *dg;
	RsDistribGrpKey *dgk;
	RsDistribSignedMsg *dsm;

	/* in order of frequency */
	if (NULL != (dsm = dynamic_cast<RsDistribSignedMsg *>(i)))
	{
		return sizeSignedMsg(dsm);
	}
	else if (NULL != (dg = dynamic_cast<RsDistribGrp *>(i)))
	{
		return sizeGrp(dg);
	}
	else if (NULL != (dgk = dynamic_cast<RsDistribGrpKey *>(i)))
	{
		return sizeGrpKey(dgk);
	}

	return 0;
}

bool     RsDistribSerialiser::serialise(RsItem *i, void *data, uint32_t *pktsize)
{
	RsDistribGrp *dg;
	RsDistribGrpKey *dgk;
	RsDistribSignedMsg *dsm;

	if (NULL != (dsm = dynamic_cast<RsDistribSignedMsg *>(i)))
	{
		return serialiseSignedMsg(dsm, data, pktsize);
	}
	else if (NULL != (dg = dynamic_cast<RsDistribGrp *>(i)))
	{
		return serialiseGrp(dg, data, pktsize);
	}
	else if (NULL != (dgk = dynamic_cast<RsDistribGrpKey *>(i)))
	{
		return serialiseGrpKey(dgk, data, pktsize);
	}
	return false;
}

RsItem *RsDistribSerialiser::deserialise(void *data, uint32_t *pktsize)
{
	/* get the type and size */
	uint32_t rstype = getRsItemId(data);

	if ((RS_PKT_VERSION_SERVICE != getRsItemVersion(rstype)) ||
		(RS_SERVICE_TYPE_DISTRIB != getRsItemService(rstype))) 
	{
		return NULL; /* wrong type */
	}

	switch(getRsItemSubType(rstype))
	{
		case RS_PKT_SUBTYPE_DISTRIB_GRP:
			return deserialiseGrp(data, pktsize);
			break;
		case RS_PKT_SUBTYPE_DISTRIB_GRP_KEY:
			return deserialiseGrpKey(data, pktsize);
			break;
		case RS_PKT_SUBTYPE_DISTRIB_SIGNED_MSG:
			return deserialiseSignedMsg(data, pktsize);
			break;
		default:
			return NULL;
			break;
	}
	return NULL;
}

/*************************************************************************/
/*************************************************************************/

