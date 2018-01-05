// Final Project | Javascript | jwq1

// global variable section
// var example = [];

// Enforce strict js code conventions
"use strict";

// Render the product on screen.
$(function retrieveJSON() {


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
    .fail(function(data, textStatus, errorThrown) {
      // Log an error to the browser.
      console.log(errorThrown.toString());
    });
  }

  // Get the element id attribute when a product is clicked
  $("#recently_added_products").click(function(event) {
    // Get id of clicked element's parent
    var product_id = $(event.target).parent().attr("id");
    console.log("element id: " + product_id)

    // If the user clicked on a product, return product data.
    if ( Number(product_id) >= 0 && Number(product_id) <= 1000 ) {
      // Create parameters for Flask.url_for() method.
      var parameters = {
        id: product_id
      }

      // Retrieve the desired product info.
      getProductInfo(parameters, function(productInfo) {
        // If no JSON was found, tell the user.
        if (typeof(productInfo) == "undefined") {

          // TODO: Return an error message to the window.
          console.log("404 Error: Product support is on top of this (kind of)")
        }
        // TODO: Otherwise, render the product using the JSON object.
          // TODO: pass JSON to the update() function to render product info.

      });
    } else {
      // Otherwise, if the user did not click on a product, return an error.
      console.log("Error: Please click on a product to view it.")
    }


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
