
#include <Request.hpp>
#include <Response.hpp>
#include <Skill.hpp>

void my_awesome_callback(const Alice::Request& request,
                         Alice::Response& response) {
  if (request.Command() == "Hello") {
    Alice::Button first_button("Print on button", {}, "http://example.com/",
                               true);
    Alice::Button second_button("Print on button", {}, "http://example.com/",
                                true);
    response.PushButton(first_button);
    response.PushButton(second_button);
    Alice::ButtonPicture button_picture("Print on button",
                                        "http://example.com/", {});
    Alice::Card card("BigImage", "1027858/46r960da47f60207e924",
                     "Title for image", "Description of image", button_picture);
    response.SetCard(card);
    response.SetText("Hi, dear friend!");
    response.SetTts("Hi, dear friend!");
    response.SetEndSession(false);
  }
  return;
}

void buy_elephant_callback(const Alice::Request& request,
                           Alice::Response& response) {
  if (request.Command() == "") {
      std::string title = "Buy an elephant!";
    } else {
      std::string title =
          "Everyone said " + request.Command() + ", but you buy an elephant!";
    }
    response.SetText(title);
    response.SetTts(title);
    Alice::Button button("I give up", {"json"},
                         "https://yandex.ru/images/"
                         "search?pos=1&img_url=https%3A%2F%2Fsummerboard.ru%"
                         "2Fimages%2Felephants_"
                         "wallpapers%2F39_elephant.jpg&text=%D1%84%D0%BE%D1%82%"
                         "D0%BE%20%D1%81%D0%"
                         "BB%D0%BE%D0%BD%D0%B0&lr=213&rpt=simage",
                         true);
    response.PushButton(button);
    response.SetEndSession(false);
    return;
  }
  response.SetText("");
  response.SetTts("");
  response.SetEndSession(true);
}

int main() {
  Skill s;
  s.SetCallback(buy_elephant_callback);
  s.Run();
  return 0;
}
