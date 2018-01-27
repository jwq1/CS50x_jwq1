// Final Project | Javascript | jwq1

// global variable section
// var example = [];

// Enforce strict js code conventions
"use strict";

// Check what kind of content to load when the document is ready.
$(function(){

  // Get product data when user navigates to a product page.
  if ( !!(document.querySelector(".product-page")) ) {
    // Pull the id from the URL, then return a JSON object.
    // Display data on screen when fetch resolves.
    retrieveJSON(getSearchParams());

  }

  // If there are product thumbnails on the page, then make them clickable.
  if ( !!(document.querySelector(".clickable-products")) ) {


    // Small TODO: Update this to add a listener on all the products on page.
    // Small TODO: use the event object to select the appropriate product.
    // Keep track of the products we have on screen.
    // BUG: This only listens for clicks on the first product on the page, not all.
    var productWasClicked = document.querySelector(".clickable-products");

    // TODO: Replace with a promise chain.
    // Promises will ensure functions call at the correct time.
    // JSON is required before document set.

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


    });

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


  // Create parameters for Flask.url_for() method.
  var parameters = {
    id: product_id
  }


  // Set URL to find the product json.
  var productUrl = Flask.url_for("getProductJSON", parameters);
  console.log('');
  console.log('productUrl built by Flask.url_for');
  console.log(productUrl);


  // Fetch product information.
  fetch(productUrl).then(function(response) {
    if(response.ok) {
      response.json().then(function(json) {

        // Print the data to the console for testing.
        console.log('');
        console.log('Success: fetch resolved!')
        console.log('The JSON data is below.')
        console.log(json);
        displayProduct(json);
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

}

// Get the product id when it is clicked.
function getIdOnClick(productClicked) {

  // TODO: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise
    // Apply await() using the Promise constructor

  // Get the id of a product when it is clicked.
  var productIdOfClicked = productClicked.id


  // Return the product's id.
  return productIdOfClicked


}


// Redirect user to the Product page
function renderProductPage(productIdentificationNumber) {

  var parameters = {
    id: productIdentificationNumber
  }

  // Render the product page with the selected product name and id.
  window.location.replace(Flask.url_for("renderProductPage", parameters));

}


// Display the product information on the page
function displayProduct(jsonOfProductInfo) {

  // Select DOM elements by css class.
  // document.querySelector

  // Select product name.
  var prodPageName = document.querySelector('.product-name');
  // Select brand.
  var prodPageBrand = document.querySelector('.brand');

  // Select product image.
  var prodPageImage = document.querySelector('.product-image');

  // Select price.
  var prodPagePrice = document.querySelector('.price');

  // Select description.
  var prodPageDescription = document.querySelector('.description');

  // Select characteristics
  var prodPageCharacteristics = document.querySelector('.characteristics');

  // Select references.
  // Select ordered list of references.
  var prodPageReferences = document.querySelector('.references-list');


  // Store JavaScript Object Notation JSON
  // in a variable to access later.
  var productJsonInfo = jsonOfProductInfo;


    // Available product info.
    // id
    // category_id
    // product_name
    // link
    // description
    // image
    // brand
    // price

    // Available reference info.
    // id
    // product_id
    // title
    // link


  // Set content.
  // Element.textContent

  // Set product name.
  // Pull product name from JavaScript object.
  prodPageName =
  // Set text content to equal JavaScript object content.
  // Set id of product name.
  // Set brand.

  // Set product image.

  // Set link.

  // Set price.

  // Set description.

  // Set characteristics
    // Populate with empty state values
    // until characteristics are available.
    // TODO: Create characteristics in DB.
    // See the productJSON.html note
    // for details about structure.


  // Set references.
    // Create list item.

    // Loop through all references for product.
      // Create reference variable.
      // Make it an anchor element.
        // Set text content to title.
        // Set href attribute to link.
      // Append to the list item.

    // Append list items to ordered list.


};

// TODO: Render "edit product info" UI.


// TODO: Create generic page update function for interactive tasks.
