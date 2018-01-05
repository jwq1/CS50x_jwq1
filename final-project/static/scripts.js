// Final Project | Javascript | jwq1

// global variable section
// var example = [];

// Enforce strict js code conventions
"use strict";

// Render the product on screen.
function retrieveJSON() {

  //TODO: Call function upon click of product name.


  // Create parameters for Flask.url_for() method.
  var parameters = {
    id: id_number
  }

  // Get the JSON with $.getJSON() & Flask.url_for().
    // Use Flask.url_for("product", parameters) to generate JSON url.
  function getProductInfo (parameters, callback) {
    $.getJSON(Flask.url_for("product"), parameters)
    // A callback executed upon successful retrieval.
    .done(function(data, textStatus, jqXHR) {
      console.log(textStatus)
      console.log(jqXHR)
      callback(jqXHR)
    })
    // A callback executed upon failed retrieval.
    .fail(function(data, textStatus, jqXHR) {
      // Log an error to the browser.
      console.log(errorThrown.toString());
    });
  }

  // Retrieve the desired product info.
  getProductInfo(parameters, function(productInfo) {
    // If no JSON was found, tell the user.
    if (typeof(productInfo) == "undefined") {

      // TODO: Get the html window element.

      // TODO: Return an error message to the window.
        // (e.g. 404: no articles for this location)
    }
  });

  // TODO: pass the variable with our JSON data to the update() function
    // update() manipulates the DOM objects to display the info we passed.


}

// Edit product information.
function editProduct() {
  var jsSuccess = 'Successfully used Javascript';

  alert(jsSuccess);

};



// Updates product search and/or product specific changes.
function updateDisplay(product_json) {

  // TODO: Get element I want to change from html
    // https://learn.jquery.com/using-jquery-core/jquery-object/#the-jquery-object

  // TODO: Use the .map() method to go through each object on the product page
    // TODO: Use the .filter() method to select the relevant info from our JSON
    // TODO: change the object selected by .map() with the relevant JSON data

    // TODO: use the .html() method to set the element on screen with our new info



};
