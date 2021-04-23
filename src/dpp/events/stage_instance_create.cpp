#include <dpp/discord.h>
/************************************************************************************
 *
 * D++, A Lightweight C++ library for Discord
 *
 * Copyright 2021 Craig Edwards and D++ contributors 
 * (https://github.com/brainboxdotcc/DPP/graphs/contributors)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ************************************************************************************/
#include <dpp/event.h>
#include <string>
#include <iostream>
#include <fstream>
#include <dpp/discordclient.h>
#include <dpp/discord.h>
#include <dpp/cache.h>
#include <dpp/stringops.h>
#include <nlohmann/json.hpp>
#include <dpp/discordevents.h>

using json = nlohmann::json;

namespace dpp { namespace events {

using namespace dpp;

/**
 * @brief Handle event
 * 
 * @param client Websocket client (current shard)
 * @param j JSON data for the event
 * @param raw Raw JSON string
 */
void stage_instance_create::handle(DiscordClient* client, json &j, const std::string &raw) {
	if (client->creator->dispatch.stage_instance_create) {
		json& d = j["d"];
		dpp::stage_instance_create_t sic(client, raw);
		sic.id = SnowflakeNotNull(&d, "id");
		sic.channel_id = SnowflakeNotNull(&d, "channel_id");
		sic.guild_id = SnowflakeNotNull(&d, "channel_id");
		sic.privacy_level = dpp::Int8NotNull(&d, "privacy_level");
		sic.topic = StringNotNull(&d, "topic");
		client->creator->dispatch.stage_instance_create(sic);
	}
}

}};