// Final Project | Javascript | jwq1

// global variable section
// var example = [];

// Enforce strict js code conventions
"use strict";

// Render the product on screen.
$(function retrieveJSON() {


  // Get the element id attribute when a product is clicked
  $("#recently_added_products").click(function(event) {
    // Get id of clicked element's parent
    var product_id = $(event.target).parent().attr("id");
    console.log("element id: ")
    console.log(product_id)

    // Create parameters for Flask.url_for() method.
    var parameters = {
      id: product_id
    }
    console.log("parameters:")
    console.log(parameters)

    // Get the JSON with $.getJSON() & Flask.url_for().
    // Use Flask.url_for("product", parameters) to generate JSON url.
    var jsPromise = Promise.resolve(
      $.getJSON(Flask.url_for("product"), parameters)
    )

    // Retrieve the desired product info through a promise.
    jsPromise.then(function(response) {
      console.log("response")
      console.log(response)
    }, function(xhrObj) {
      console.log("xhrObj")
      console.log(xhrObj)
    })

  });


});



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
