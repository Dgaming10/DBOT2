#include <iostream>
#include <dpp/dpp.h>
#include <dotenv.h>

using namespace dotenv;
using namespace std;

int main()
{
    env.load_dotenv("/home/dgaming10/Desktop/DBOT2/.env");
    cout << env["DISCORD_API_KEY"] << endl;

    dpp::cluster bot(env["DISCORD_API_KEY"]);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("ping", "Check connection", bot.me.id));
        }
    });

    bot.start(dpp::st_wait);

    return 0;
}
