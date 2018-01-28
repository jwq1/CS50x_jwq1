// Final Project | Javascript | jwq1

// global variable section
// var example = [];

// Enforce strict js code conventions
"use strict";

// Check what kind of content to load when the document is ready.
$(function(){

  // TODO: Edit the product page

  // Get product data when user navigates to a product page.
  if ( !!(document.querySelector(".product-page")) ) {

    // Pull the id from the URL, then return a JSON object.
    // Display data on screen when fetch resolves.
    retrieveJSON(getSearchParams());

  }

  // If there are product thumbnails on the page, then make them clickable.
  if ( !!(document.querySelector(".clickable-products")) ) {

    // Listen for clicks on all the products on the screen.
    var productWasClicked = document.querySelectorAll(".clickable-products");

    // Loop through all the products on the page.
    for (var i = 0; i < productWasClicked.length; i++) {

      // Listen for clicks on those products.
      productWasClicked[i].addEventListener('click', function(e) {

        // Select the product which was clicked.
        // Get the id of that product.
        // Save the id as a number.
        var productIdNumber = Number(getIdOnClick(e.currentTarget));

        // Render the product page.
        // Set the URL to include the product ID.
        renderProductPage(productIdNumber);

      });
    }
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

  // Set the parameters for the URL.
  var parameters = {
    id: product_id
  };

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

  // Set product parameters
  var parameters = {
    id: productIdentificationNumber
  }

  // Render the product page with the selected product name and id.
  window.location.replace(Flask.url_for("renderProductPage", parameters));

}


// Display the product information on the page
function displayProduct(jsonOfProductInfo) {


  // v v v Select DOM elements by css class. v v v

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


  // v v v Set content. v v v

  // Set product name.
  prodPageName.textContent = productJsonInfo['product_name'];
  // Set id of product name.
  prodPageName.setAttribute('id', productJsonInfo['product_name']);

  // Set brand.
  prodPageBrand.textContent = productJsonInfo['brand'];

  // Set product image.
  prodPageImage.setAttribute('src', productJsonInfo['image']);

  // Set price.
  prodPagePrice.textContent = "$" + productJsonInfo['price'];

  // Set description.
  prodPageDescription.textContent = productJsonInfo['description'];

  // Set characteristics.
  // Populate with empty state values
  // until characteristics are available.
  prodPageCharacteristics.textContent = "This section is under construction.";
    // TODO: Create characteristics in DB.
    // See the productJSON.html note
    // for details about structure.

  // Set references.
  // Create list item.
  var referenceListItem = document.createElement('li');

  // Loop through all references for product.
  for (var i = 0; i < productJsonInfo['reference_titles'].length; i++) {

    // Create reference variable.
    // Make it an anchor element.
    var referenceItemContent = document.createElement('a');
    // Set text content to title.
    referenceItemContent.textContent = productJsonInfo['reference_titles'][i];
    // Set href attribute to link.
    referenceItemContent.setAttribute("href", productJsonInfo['reference_links'][i]);
    // Append to the list item.
    referenceListItem.appendChild(referenceItemContent);

    // Append list items to ordered list.
    prodPageReferences.appendChild(referenceListItem);

  }
};

// TODO: Render "edit product info" UI.

  // Create form elements for all the required page elements.
  // Submit the form via the POST method.

    // Create an input element for each form.

    // Populate placeholder values with the current content of the element.

  // For the references, create multiple form elements with multiple inputs.

    // For each form, create a title input and link input.

    // Populate placeholder values with the current content of the element.

  // Create a button element for submission.

  // Listen for clicks on the submit button


// TODO: Create generic page update function for interactive tasks.
