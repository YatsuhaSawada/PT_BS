#include "MyBot.h"
#include <dpp/dpp.h>

/* Be sure to place your token in the line below.
 * Follow steps here to get a token:
 * https://dpp.dev/creating-a-bot-application.html
 * When you invite the bot, be sure to invite it with the 
 * scopes 'bot' and 'applications.commands', e.g.
 * https://discord.com/oauth2/authorize?client_id=940762342495518720&scope=bot+applications.commands&permissions=139586816064
 */
const std::string    BOT_TOKEN    = "";

int main()
{
	/* Create bot cluster */
	dpp::cluster bot(BOT_TOKEN);

	/* Output simple log messages to stdout */
	bot.on_log(dpp::utility::cout_logger());

	/* Handle slash command */
	bot.on_slashcommand([](const dpp::slashcommand_t& event) {
		if (event.command.get_command_name() == "ping") {
			event.reply("Pong!");
		}
        /* Check which command they ran */
        if (event.command.get_command_name() == "embed") {
            /* Create an embed */
            dpp::embed embed = dpp::embed()
                .set_color(dpp::colors::sti_blue)
                .set_title("Some name")
                .set_url("https://dpp.dev/")
                .set_author("Some name", "https://dpp.dev/", "https://dpp.dev/DPP-Logo.png")
                .set_description("Some description here")
                .set_thumbnail("https://dpp.dev/DPP-Logo.png")
                .add_field(
                    "Regular field title",
                    "Some value here"
                )
                .add_field(
                    "Inline field title",
                    "Some value here",
                    true
                )
                .add_field(
                    "Inline field title",
                    "Some value here",
                    true
                )
                .set_image("https://dpp.dev/DPP-Logo.png")
                .set_footer(
                    dpp::embed_footer()
                    .set_text("Some footer text here")
                    .set_icon("https://dpp.dev/DPP-Logo.png")
                )
                .set_timestamp(time(0));

            /* Create a message with the content as our new embed. */
            dpp::message msg(event.command.channel_id, embed);

            /* Reply to the user with the message, containing our embed. */
            event.reply(msg);
        }
	});

	/* Register slash command here in on_ready */
	bot.on_ready([&bot](const dpp::ready_t& event) {
		/* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
		if (dpp::run_once<struct register_bot_commands>()) {
            {
               auto r = bot.global_command_create_sync(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
               //nlohmann::json j;
               //to_json(j, r);
               //std::cout << j.dump(4) << std::endl;
            }
            {
                auto r = bot.global_command_create_sync(dpp::slashcommand("embed", "Send a test embed!", bot.me.id));
                //nlohmann::json j;
                //to_json(j, r);
                //std::cout << j.dump(4) << std::endl;
            }
        }
        });

    bot.start(dpp::st_wait);


    return 0;
}

