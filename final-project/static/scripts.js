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


// Redirect user to the Product page
$(function redirectToProduct() {

  // Listen for when the user clicks a product.
  $("#recently_add_products").click(function(event) {

    // TODO: Get id of the product clicked

    // TODO: Save the id and name of the product selected.

    // TODO: Render the product page with the selected product name and id.

  });

});


// Display the product information on the page
$(function displayProduct() {


  // TODO: Listen for when a product page loads.

    // TODO: Get the product id.

    // TODO: Get the product information based on id.

    // TODO: Set the relevant elements to display product information.

      // TODO: Select the desired DOM element.

      // TODO: Parse the responseJSON for the data to show on screen.


});
