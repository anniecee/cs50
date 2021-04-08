function showoptions()
{
    //Get name from guest first
    let name = document.querySelector("#guestname").value;

    //Special message for Jeff
    if (name === "Jeff" || name === "Jeffrey") {
        document.querySelector("#sayhello").innerHTML = "Oh my god, handsome " + name +" &#128525! I'm so glad that you're here.";
    }
    else if (name === "Boba") {
        document.querySelector("#sayhello").innerHTML = "Hey, don't you pretend that you're my Boba the teddy bear. Boba will not like it."
    }
    else if (name === "") {
        document.querySelector("#sayhello").innerHTML = "Hello buddy!";
    }
    else {
        document.querySelector("#sayhello").innerHTML = "Hello, "+ name + "!";
    }

    //Display options for guests to choose
    document.querySelector("#gettoknow").style.display = "block";

}

function accesspage() {
  var selected = document.getElementById('pages');

  var option = selected.options[selected.selectedIndex].value;

  window.open(option + ".html", "_self");
}