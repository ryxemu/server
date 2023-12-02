#ifndef COMMON_SAY_LINK_H
#define COMMON_SAY_LINK_H


#include "types.h"

#include <string>



struct ServerLootItem_Struct;

namespace EQ
{
	class ItemInstance;
	struct SayLinkBody_Struct;
	struct ItemData;

	namespace saylink {
		enum SayLinkType {
			SayLinkBlank = 0,
			SayLinkItemData,
			SayLinkLootItem,
			SayLinkItemInst
		};

		extern bool DegenerateLinkBody(SayLinkBody_Struct& say_Link_body_struct, const std::string& say_link_body);
		extern bool GenerateLinkBody(std::string& say_link_body, const SayLinkBody_Struct& say_link_body_struct);

	}/*saylink*/

	struct SayLinkBody_Struct {
		uint8 action_id;		/* %1X */
		uint16 item_id;			/* %05X */
	};

	struct SayLinkProxy_Struct : SayLinkBody_Struct {
		const char* text;
	};

	class SayLinkEngine {
	public:
		SayLinkEngine();

		void SetLinkType(saylink::SayLinkType  link_type) { m_LinkType = link_type; }
		void SetItemData(const EQ::ItemData* item_data) { m_ItemData = item_data; }
		void SetLootData(const ServerLootItem_Struct* loot_data) { m_LootData = loot_data; }
		void SetItemInst(const EQ::ItemInstance* item_inst) { m_ItemInst = item_inst; }

		// mainly for saylinks..but, not limited to
		void SetProxyActionID(uint8 proxy_action_id) { m_LinkProxyStruct.action_id = proxy_action_id; }
		void SetProxyItemID(uint32 proxy_item_id) { m_LinkProxyStruct.item_id = proxy_item_id; }

		void SetProxyText(const char* proxy_text) { m_LinkProxyStruct.text = proxy_text; } // overrides standard text use
		void SetTaskUse() { m_TaskUse = true; }

		const std::string& GenerateLink();
		bool LinkError() { return m_Error; }

		const std::string& Link() { return m_Link; }			// contains full string format: '/12x' '<LinkBody>' '<LinkText>' '/12x'
		const std::string& LinkBody() { return m_LinkBody; }	// contains string format: '<LinkBody>'
		const std::string& LinkText() { return m_LinkText; }	// contains string format: '<LinkText>'

		static std::string GenerateQuestSaylink(std::string saylink_text, bool silent, std::string link_name);

		void Reset();

	private:
		void generate_body();
		void generate_text();

		int m_LinkType;
		const EQ::ItemData* m_ItemData;
		const ServerLootItem_Struct* m_LootData;
		const EQ::ItemInstance* m_ItemInst;

		SayLinkBody_Struct m_LinkBodyStruct;
		SayLinkProxy_Struct m_LinkProxyStruct;
		bool m_TaskUse;
		std::string m_Link;
		std::string m_LinkBody;
		std::string m_LinkText;
		bool m_Error;
	};

}

class Saylink {
public:
	static std::string Create(std::string saylink_text, bool silent, std::string link_name);
};

#endif /* COMMON_SAY_LINK_H */