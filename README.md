# random-rps

A simple Rock Paper Scissors game using the NodeMCU ESP8266 module and Espressif systems interpreter for Javascript.
This is implemented using wia, you can sign up and login [here](https://dashboard.wia.io/login).

- - - -

### installation ###
* Make a wia account,create a space with desired name and add device. Pick Espressif and then ESP8266. If a configuration screen popped up and is 'listening to your device' is called, you may skip.
* After that you get the dashboard screen and you want your device secret key to be inserted in one of the variable in the arduino code.
* Head to flow and create a flow, name it _rpsgame_ and in the builder->trigger drag&drop "Event Created". The device configured should be visible, select that and name it _buttonPress_.
  * builder->action drag&drop "Event" then name it _peepoSad_.
  * builder->logic drag&drop "Run Function" then cp&pste this snippet of JS code: 
```javascript
var items = [
    'Rock',
    'Paper',
    'Scissor'
];

var item = items[Math.floor(Math.random()*items.length)];
output.body.data = item;
```
 *  Connect the flow as is below.
 
 ![picture alt](https://github.com/roidsaja/random-rps8266/blob/master/flow.png)
 
* It now works as a RPS RNG generator, simply press on the 'flash' button in the ESP8266. However this is without any display so to embed the wia widget onto an HTML, head over to the Things menu and select your device. In the overview add a widget:
  * Fill in desired name, widget type in Text, widget parameters in latest event and event name _peepoSad_. Update Widget.
* A widget card will be made and on the top right, select the visibility to be _Anyone can view this widget and embed it in any website._
* Copy the Embed into the HTML and run it as localhost
