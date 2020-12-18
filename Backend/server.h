#pragma once
#include "athena.h"
#include "calendar.h"
#include "collections.h"
#include "common_core.h"
#include "common_public.h"
#include "creative.h"
#include "fortnite-game.h"
#include "profile.h"
#include "../includes/framework.h"

using namespace httplib;

inline HANDLE hServer = INVALID_HANDLE_VALUE;
inline Server app;

namespace server
{
	inline void init()
	{
		//yes one file for now. -kemo

		//================================ 204s =================================
		app.Get("/waitingroom/api/waitingroom", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Get(R"(/fortnite/api/game/v2/grant_access/(.*))", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Post(R"(/datarouter/api/v1/public/(.*))", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Get(R"(/presence/(.*))", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Get(R"(/party/api/v1/Fortnite/user/(.*)/notifications/undelivered/count)", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Get("/fortnite/api/game/v2/br-inventory/account/NeoniteUser", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Get(R"(/socialban/api/public/v1/(.*))", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Get(R"(/api/v1/events/(.*))", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Get(R"(/content-controls/(.*))", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Get(R"(/fortnite/api/cloudstorage/user/(.*)/(.*))", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Put(R"(/fortnite/api/cloudstorage/user/(.*)/(.*))", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Delete("/account/api/oauth/sessions/kill", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Delete(R"(/account/api/oauth/sessions/kill/(.*))", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Get(R"(/party/api/v1/Fortnite/parties/(.*))", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Delete(R"(/party/api/v1/Fortnite/parties/(.*))", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Get(R"(/fortnite/api/game/v2/br-inventory/account/(.*))", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Post(R"(/presence/(.*))", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		app.Get(R"(/statsproxy/api/(.*))", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		//================================ Empty Arrays =================================

		app.Get(R"(/account/api/public/account/(.*)/externalAuths)", [](const Request& req, Response& res)
		{
			res.set_content("[]", "application/json");
		});

		app.Get("/fortnite/api/game/v2/enabled_features", [](const Request& req, Response& res)
		{
			res.set_content("[]", "application/json");
		});

		app.Get(R"(/fortnite/api/receipts/v1/account/(.*)/receipts)", [](const Request& req, Response& res)
		{
			res.set_content("[]", "application/json");
		});

		app.Get(R"(/friends/(.*))", [](const Request& req, Response& res)
		{
			res.set_content("[]", "application/json");
		});

		//================================ Dynamics =================================

		app.Get("/lightswitch/api/service/bulk/status", [](const Request& req, Response& res)
		{
			const auto j =
			R"(
		[{
			"serviceInstanceId": "fortnite",
			"status": "UP",
			"message": "Neonite++",
			"maintenanceUri": null,
			"allowedActions": ["PLAY", "DOWNLOAD"],
			"banned": false
		}]
		)"_json;
			res.set_content(j.dump(), "application/json");
		});

		app.Get(R"(/fortnite/api/v2/versioncheck/(.*))", [](const Request& req, Response& res)
		{
			const auto j = R"({"type": "NO_UPDATE"})"_json;
			res.set_content(j.dump(), "application/json");
		});

		app.Get("/content/api/pages/fortnite-game/", [](const Request& req, Response& res)
		{
			json j = fortniteGame();
			res.set_content(j.dump(), "application/json");
		});

		app.Get("/fortnite/api/calendar/v1/timeline", [](const Request& req, Response& res)
		{
			json j = calendar();
			res.set_content(j.dump(), "application/json");
		});

		app.Get("/account/api/public/account", [](const Request& req, Response& res)
		{
			auto account_id = req.get_param_value("accountId");
			json j = {
				{"id", account_id},
				{"displayName", account_id},
				{"externalAuths", json({})}
			};
			res.set_content(j.dump(), "application/json");
		});

		app.Get(R"(/account/api/public/account/(.*))", [](const Request& req, Response& res)
		{
			auto account_id = static_cast<std::string>(req.matches[1]);
			json j = {
				{"id", account_id},
				{"displayName", account_id},
				{"externalAuths", json({})}
			};
			res.set_content(j.dump(), "application/json");
		});

		app.Get(R"(/fortnite/api/game/v2/privacy/account/(.*))", [](const Request& req, Response& res)
		{
			auto account_id = static_cast<std::string>(req.matches[1]);
			json j = {
				{"accountId", account_id},
				{"optOutOfPublicLeaderboards", false}
			};
			res.set_content(j.dump(), "application/json");
		});

		app.Get(R"(/friends/api/public/blocklist/(.*))", [](const Request& req, Response& res)
		{
			const auto j = R"({ "blockedUsers": [] })"_json;
			res.set_content(j.dump(), "application/json");
		});

		app.Get(R"(/friends/api/v1/(.*)/settings)", [](const Request& req, Response& res)
		{
			const auto j = R"({ "blockedUsers": [] })"_json;
			res.set_content(j.dump(), "application/json");
		});

		app.Post(R"(/fortnite/api/game/v2/tryPlayOnPlatform/account/(.*))", [](const Request& req, Response& res)
		{
			res.set_content("true", "text/plain");
		});

		app.Get(R"(/affiliate/api/public/affiliates/slug/(.*))", [](const Request& req, Response& res)
		{
			const auto j =
			R"(
		{
			"id": "aabbccddeeff11223344556677889900",
			"slug": "neonite++",
			"displayName": "neonite++",
			"status": "ACTIVE",
			"verified": true
		}
		)"_json;
			// sorry ytrs :pepelaugh: -kemo
			res.set_content(j.dump(), "application/json");
		});

		//==> TO BE IMPLEMENTED <==
		app.Get("/fortnite/api/cloudstorage/system", [](const Request& req, Response& res)
		{
			res.status = 204;
		});

		//==> TO BE IMPLEMENTED <==
		app.Get(R"(/fortnite/api/cloudstorage/user/(.*))", [](const Request& req, Response& res)
		{
			res.set_content("[]", "application/json");
		});

		//==> TO BE IMPLEMENTED <==
		app.Get("/fortnite/api/storefront/v2/keychain", [](const Request& req, Response& res)
		{
			const auto j = R"(["A93064DA8BDA456CADD2CD316BE64EE5:nziBPQTfuEl4IRK6pOaovQpqQC6nsMQZFTx+DEg62q4=:CID_NEONITE_TEMP"])"_json;
			res.set_content(j.dump(), "application/json");
		});

		app.Get(R"(/party/api/v1/Fortnite/user/(.*))", [](const Request& req, Response& res)
		{
			const auto j = R"({ "current": [], "pending": [], "invites": [], "pings": [] })"_json;
			res.set_content(j.dump(), "application/json");
		});

		//OAuth
		app.Get("/account/api/oauth/verify", [](const Request& req, Response& res)
		{
			auto token = static_cast<std::string>(req.get_header_value("Authorization"));
			token.erase(token.begin(), token.begin() + 7);
			json j = {
				{"access_token", token},
				{"expires_in", 28800},
				{"expires_at", "9999-12-31T23:59:59.999Z"},
				{"token_type", "bearer"},
				{"refresh_token", "neonitepprefreshtokenplaceholder"},
				{"refresh_expires", 115200},
				{"refresh_expires_at", "9999-12-31T23:59:59.999Z"},
				{"account_id", "neonitepp"},
				{"client_id", "neoniteppclientidplaceholder"},
				{"internal_client", "true"},
				{"client_service", "fortnite"},
				{"displayName", "neoniteppplayer"},
				{"app", "fortnite"},
				{"in_app_id", "neonitepp"},
				{"device_id", "neoniteppdeviceidplaceholder"}
			};
			res.set_content(j.dump(), "application/json");
		});

		app.Post("/account/api/oauth/token", [](const Request& req, Response& res)
		{
			json j;
			if (util::getQuery(req.body, "grant_type") == "client_credentials")
			{
				j = {
					{"access_token", util::genRandom(32)},
					{"expires_in", 28800},
					{"expires_at", "9999-12-31T23:59:59.999Z"},
					{"token_type", "bearer"},
					{"client_id", "neoniteppclientidplaceholder"},
					{"internal_client", "true"},
					{"client_service", "fortnite"},
				};
			}
			else
			{
				std::string displayName;
				std::string body = util::urlDecode(req.body);

				if (util::getQuery(body, "email") != "failed")
				{
					displayName = util::sSplit(util::getQuery(body, "email"), "@");
				}
				else if (util::getQuery(body, "username") != "failed")
				{
					displayName = util::sSplit(util::getQuery(body, "username"), "@");
				}
				else displayName = "NeonitePPUser";

				j = {
					{"access_token", util::genRandom(32)},
					{"expires_in", 28800},
					{"expires_at", "9999-12-31T23:59:59.999Z"},
					{"token_type", "bearer"},
					{"account_id", displayName},
					{"client_id", "ec684b8c687f479fadea3cb2ad83f5c6"},
					{"internal_client", true},
					{"client_service", "fortnite"},
					{"displayName", displayName},
					{"app", "fortnite"},
					{"in_app_id", displayName},
					{"device_id", "5dcab5dbe86a7344b061ba57cdb33c4f"}
				};
			}

			res.set_content(j.dump(), "application/json");
		});

		//Profile
		app.Post(R"(/fortnite/api/game/v2/profile/(.*)/client/(.*))", [](const Request& req, Response& res)
		         {
			         //TODO: handle this somewhere else.
			         std::string account_id = static_cast<std::string>(req.matches[1]);
			         std::string command = static_cast<std::string>(req.matches[2]);
			         std::string profile_id = "common_core";
			         int rvn = -1;
			         boost::posix_time::ptime t = boost::posix_time::microsec_clock::universal_time();
			         auto date = to_iso_extended_string(t);
			         date = date.substr(0, date.size() - 3) + "Z";
			         json profileData;

			         if (req.has_param("rvn")) rvn = std::stoi(req.get_param_value("rvn"));
			         if (req.has_param("profileId")) profile_id = req.get_param_value("profileId");

			         if (profile_id == "athena") profileData = pAthena();
			         else if (profile_id == "common_public") profileData = pCommonPublic();
			         else if (profile_id == "creative") profileData = pCreative();
			         else if (profile_id == "collections") profileData = pCollections();
			         else profileData = pCommonCore();

			         if (profileData["rvn"].is_null()) profileData["rvn"] = 1;
			         if (profileData["commandRevision"].is_null()) profileData["commandRevision"] = 1;

			         json response = {
				         {"profileRevision", profileData["rvn"]},
				         {"profileId", profile_id},
				         {"profileChangesBaseRevision", profileData["rvn"]},
				         {"profileChanges", json::array()},
				         {"serverTime", date},
				         {"profileCommandRevision", profileData["commandRevision"]},
				         {"responseVersion", 1}
			         };

			         //mcp

			         switch (util::str2int(command.c_str()))
			         {
			         case util::str2int("ClientQuestLogin"):
			         {
				         break;
			         }
			         case util::str2int("SetCosmeticLockerSlot"):
			         {
				         auto body = json::parse(req.body);
				         auto lockerItem = body["lockerItem"].get<std::string>();
				         auto items = profileData["items"];
				         auto item = items[lockerItem];
				         if (item.is_null())
				         {
					         //TODO: add mpc error handling.
				         }
				         auto category = body["category"].get<std::string>();
				         auto locker_slot_data = item["attributes"]["locker_slots_data"];
				         auto lockerSlot = locker_slot_data["slots"][category];
				         if (lockerSlot.is_null())
				         {
					         //Emotes and wraps
				         }
				         auto itemsArray = lockerSlot["items"];
				         bool bChanged = false;

				         auto slotIndex = body["slotIndex"].get<int>();
				         if (!slotIndex) slotIndex = 0;

				         if (slotIndex == -1)
				         {
					         //Apply to all
				         }
				         else
				         {
					         if (slotIndex >= 0 && itemsArray.size())
					         {
						         if (itemsArray[slotIndex] != body["itemToSlot"])
						         {
							         itemsArray[slotIndex] = body["itemToSlot"];
							         bChanged = true;
						         }
					         }
							 profileData["items"][lockerItem]["attributes"]["locker_slots_data"]["slots"][category]["items"] = itemsArray;
				         }

				         if (body["variantUpdates"].size() != 0)
				         {
					         //variants update
				         }

				         if (bChanged)
				         {
					         //TODO: make this a function.

					         auto itemId = body["lockerItem"].get<std::string>();
					         auto item = profileData["items"][itemId];
					         //if (item.is_null()) return false;
					         if (item["attributes"].is_null())
					         {
						         item["attributes"] = json::object();
					         }
					         item["attributes"]["locker_slots_data"] = locker_slot_data;
					         json changes = {
						         {"changeType", "itemAttrChanged"},
						         {"itemId", itemId},
						         {"attributeName", "locker_slots_data"},
						         {"attributeValue", locker_slot_data}
					         };
					         response["profileChanges"].push_back(changes);
				         }

				         break;
			         }
			         case util::str2int("MarkItemSeen"):
			         {
				         //req.body.itemIds.forEach(itemId => Profile.changeItemAttribute(profileData, itemId, "item_seen", true, profileChanges));
				         /*
				          json itemsIds = json::parse(req.body)["itemsIds"];
				          for (auto& item : itemsIds.items())
				          {
					          std::string itemId = item.value();
					          response["profileChanges"].push_back({
						          {"changeType", "itemRemoved"},
						          {"itemId", itemId}
					          });
				          }
				          */
				         break;
			         }
			         }

			         if (response["profileChanges"].size() > 0)
			         {
				         profileData["rvn"] = profileData["rvn"].get<int>() + 1;
				         profileData["commandRevision"] = profileData["commandRevision"].get<int>() + 1;
						 profileData["updated"] = date;
				         response["profileRevision"] = profileData["rvn"];
				         response["profileCommandRevision"] = profileData["commandRevision"];
			         	
						 if (profile_id == "athena") profile_athena = profileData;
						 else if (profile_id == "common_public") profile_public = profileData;
						 else if (profile_id == "creative") profile_creative = profileData;
						 else if (profile_id == "collections") profile_collections = profileData;
						 else profileData = profile_core = profileData;
			         }

			         if (rvn != response["profileChangesBaseRevision"].get<int>())
			         {
				         response["profileChanges"][0] = {
					         {"changeType", "fullProfileUpdate"},
					         {"profile", profileData}
				         };
			         };

			         res.set_content(response.dump(), "application/json");
		         }
		);

		app.set_error_handler([](const auto& req, auto& res)
		{
			auto fmt = "{}";
			char buf[BUFSIZ];
			snprintf(buf, sizeof(buf), fmt, res.status);
			res.set_content(buf, "application/json");
		});

		app.listen("127.0.0.1", 5595);
	}
}
