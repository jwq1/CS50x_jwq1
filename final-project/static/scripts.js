// Final Project | Javascript | jwq1

// global variable section
// var example = [];

// Enforce strict js code conventions
"use strict";

// Check what kind of content to load when the document is ready.
$(function(){

  // If there are product thumbnails on the page, then make them clickable.
  if ( !!(document.querySelector(".clickable-products")) ) {


    // BIG TODO: Only use fetch product data after the product page has been rendered.
    // The browser's CORS security prevents cross-origin requests.
    // Answer 1:
    // https://stackoverflow.com/questions/42719041/how-to-resolve-typeerror-networkerror-when-attempting-to-fetch-resource
    // Answer 2:
    // https://stackoverflow.com/questions/37333573/fetch-with-the-wikipedia-api-results-in-typeerror-networkerror-when-attempti#37351064
    // Documentation:
    // https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS
    // Explanation:
    // These answers and documentation explain the failure in my previous code.

    // BIG TODO 2: The JSON is currently retrieved by asking Flask
    // to render a URL which returns a json. This will not work, because the url
    // would have to be different than the current page.
    // Need to get JSON from our python application without using the Flask.url_for
    // method. There must be some other way to do this, but it requires more research.
    // How does one call a python function from javascript? <-- John, answer this.


    // Small TODO: Update this to add a listener on all the products on page.
    // Small TODO: use the event object to select the appropriate product.
    // Keep track of the products we have on screen.
    var productWasClicked = document.querySelector(".clickable-products");

    // TODO: Replace with a promise chain.
    // Promises will ensure functions call at the correct time to avoid CORS error.

    // TODO: Create new promise object to get identification of product clicked
    // https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise

    // TODO: Create a new promise to render the html template for the product page.


    // TODO: Create a new promise to retrieve JSON information for that product


    // TODO: Create a new promise to update the page with the product's information


    // TODO: Chain promises together to execute functions one after another.



    // Search for product information when the user selects a product.
    productWasClicked.addEventListener('click', function() {

      // Save the id of the product.
      var productIdNumber = Number(getIdOnClick( productWasClicked ));

      // Render the product page.
      renderProductPage(productIdNumber);


      // Get information for the product our user selects.
      var productInformation = retrieveJSON(getSearchParams);


    });

  }

  // If the user is on a product page, then load product content.
  if ( !!( document.querySelector(".product-page") ) ) {

    // TODO: load relevant product content

  }

});

// Get product search parameters.
function getSearchParams() {

  // Get the parameters after the '?' in the URL.
  let params = (new URL(document.location)).searchParams;

  // Parse only the 'id=' parameter.
  let productIdentity = params.get("id");

  // Return the 'id' number of the product.
  return productIdentity;
}



// Retrieve product information in the form of a JSON.
function retrieveJSON(product_id) {

  console.log(" ");
  console.log("retreiveJSON function started");

  // Create parameters for Flask.url_for() method.
  var parameters = {
    id: product_id
  }
  console.log(" ");
  console.log("parameters:");
  console.log(parameters);

  // Set URL to find the product json.
  var productUrl = Flask.url_for('product', parameters);
  console.log('');
  console.log('productUrl built by Flask.url_for');
  console.log(productUrl);

  // Create a variable to store the products.
  var productsJsonData;

  // Fetch product information.
  fetch(productUrl).then(function(response) {
    if(response.ok) {
      response.json().then(function(json) {
        // Store the JSON data in a properly scoped variable.
        productsJsonData = json;
      })
    } else {
      // Print an error if nothing was found.
      console.log('Network request for products.json failed with response '
        + response.status
        + ': '
        + response.statusText
      );
    }
  });

  // Print the data to the console for testing.
  console.log('');
  console.log(productsJsonData);
  return productsJsonData;

  // How to resolve “TypeError: NetworkError when attempting to fetch resource.""
  // https://stackoverflow.com/questions/42719041/how-to-resolve-typeerror-networkerror-when-attempting-to-fetch-resource

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
  window.location.href = Flask.url_for("product", parameters);


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
