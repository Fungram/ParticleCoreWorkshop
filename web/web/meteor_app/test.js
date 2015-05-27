if (Meteor.isClient) {
  // counter starts at 0
  Session.setDefault('lightState', 0);

  Template.hello.helpers({
    lightState: function () {
      Meteor.http.get("https://api.particle.io/v1/devices/54ff6d066667515113491467/lights?access_token=09f02c0567877ff7a0dd88c609174107695de484", function (err, data ){
        console.log(data.data.result );
        Session.set('lightState', data.data.result);
      });
      return Session.get('lightState');

    }
  });

  Template.hello.events({
    'click button': function () {
      // increment the counter when button is clicked
      Meteor.http.post("https://api.particle.io/v1/devices/54ff6d066667515113491467/toggleLight?access_token=09f02c0567877ff7a0dd88c609174107695de484", function (results ){
        console.log("HTTP POST response received");

      });
      Meteor.http.get("https://api.particle.io/v1/devices/54ff6d066667515113491467/lights?access_token=09f02c0567877ff7a0dd88c609174107695de484", function (err, data ){
        console.log(data.data.result );
        Session.set('lightState', data.data.result);
      });
    }
  });
}

if (Meteor.isServer) {
  Meteor.startup(function () {
    // code to run on server at startup
  });
}
