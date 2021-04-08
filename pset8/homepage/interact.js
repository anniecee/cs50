function showMessage(emoji)
{
    //Display text
    document.querySelector("#response_box").style.display = "block";

    //Show message according to selected emoji
    if (emoji === "happy") {
        document.querySelector("#response_text").innerHTML = "I'm glad that you're feeling good! Hope that your whole week will be awesome. 😊";
    }
    if (emoji === "love") {
        document.querySelector("#response_text").innerHTML = "Thanks for sending love. Lots of love for you too! &#x1F495; &#x1F495;";
    }
    if (emoji === "hifive") {
        document.querySelector("#response_text").innerHTML = "You're great! High five! 🙏";
    }
    if (emoji === "sad") {
        document.querySelector("#response_text").innerHTML = "Awww why are you so sad? 😔 Let me give you a hug. 🤗";
    }
    if (emoji === "angry") {
        document.querySelector("#response_text").innerHTML = "Please don't get mad. I am scared. 😔";
    }
    if (emoji === "worry") {
        document.querySelector("#response_text").innerHTML = "Don't you worry. I will have your back no matter what! 💪";
    }
    if (emoji === "avocado") {
        document.querySelector("#response_text").innerHTML = "So I guess you must like avocado too? Ikr, who wouldn't? 😆";
    }
    if (emoji === "present") {
        document.querySelector("#response_text").innerHTML = "Awww you just sent me gift? How lovely! 😍 Wish all the best for you.";
    }
    if (emoji === "dog") {
        document.querySelector("#response_text").innerHTML = "Don't you love puppies? They are so freaking cute! 🐶";
    }
}

function accesspage() {
  var selected = document.getElementById('pages');

  var option = selected.options[selected.selectedIndex].value;

  window.open(option + ".html", "_self");
}