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
      callback(data)
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
      // Refactor: This conditional needs a longer term solution.
    if ( Number(product_id) >= 0 && Number(product_id) <= 1000 ) {
      // Create parameters for Flask.url_for() method.
      var parameters = {
        id: product_id
      }

      // Retrieve the desired product info.
      getProductInfo(parameters, function(productInfo) {
        // If no JSON was found, tell the user.
        if (typeof(productInfo) == "undefined") {

          // Log an error message.
          console.log("404 Error: Product support is on top of this (kind of)")
        }
        // Otherwise, return product info.
        console.log("productInfo: ")
        console.log(productInfo)
        return productInfo

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
