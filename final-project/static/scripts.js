// Final Project | Javascript | jwq1

// global variable section
// var example = [];

// Enforce strict js code conventions
"use strict";

// Check what kind of content to load when the document is ready.
$(function(){

  // If there are product thumbnails on the page, then make them clickable.
  if ( !!(document.querySelector(".clickable-products")) ) {

    // Keep track of the products we have on screen.
    var productWasClicked = document.querySelector(".clickable-products");

    // Search for product information when the user selects a product.
    productWasClicked.onclick = function() {

      // Save the id of the product.
      var productIdNumber = getIdOnClick( productWasClicked );

      // Get information for the product our user selects.
      var productInformation = retrieveJSON( productIdNumber );

      // Redirect to the 'View Product' page.
      renderProductPage();

    }

  }


});


// Retrieve product information in the form of a JSON.
function retrieveJSON(product_id) {

  console.log(" ")
  console.log("retreiveJSON function started")

  // Create parameters for Flask.url_for() method.
  var parameters = {
    id: product_id
  }
  console.log(" ")
  console.log("parameters:")
  console.log(parameters)

  // Get the JSON with $.getJSON() & Flask.url_for().
  // Use Flask.url_for("product", parameters) to generate JSON url.
  var getProductJSON = Promise.resolve(
    $.getJSON(Flask.url_for("getProductJSON"), parameters)
  )

  // Retrieve the desired product info through a promise.
  getProductJSON.then(function(response) {
    console.log(" ")
    console.log("Success: retrieveJSON returned response")
    console.log(response)
    var theProductInfo = response
    return theProductInfo
  }, function(xhrObj) {
    console.log(" ")
    console.log("FAILURE: no product info was returned ")
  })

}


// Get the product id when it is clicked.
function getIdOnClick(productClicked) {

  // TODO: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise
    // Apply await() using the Promise constructor

  // Get the id of a product when it is clicked.
  var productIdOfClicked = productClicked.id
  console.log(" ")
  console.log("Heard click")
  console.log("product id is " + productIdOfClicked)


  // Return the product's id.
  return productIdOfClicked


}


// Redirect user to the Product page
function renderProductPage() {

  // Render the product page with the selected product name and id.
  window.location.href = Flask.url_for("product");


}


// Display the product information on the page
function displayProduct() {


  // TODO: Listen for when a product page loads.

    // TODO: Get the product id.

    // TODO: Get the product information based on id.

    // TODO: Set the relevant elements to display product information.

      // TODO: Select the desired DOM element.

      // TODO: Parse the responseJSON for the data to show on screen.


};
