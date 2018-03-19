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

    // TODO: Chain these together in a promise so they are executed in the proper order.

    // Pull the id from the URL, then return a JSON object.
    // Display data on screen when fetch resolves.
    retrieveJSON(getSearchParams());

    // Select the edit button.
    var editButton = document.querySelector('#edit-product');
    // Listen for clicks.
    editButton.addEventListener('click', renderEditInterface, {once:false});

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

function renderEditInterface() {

  renderEditProductForm();
  insertSaveButton();
  listenForSave();

}

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
function retrieveJSON(productId) {

  // Set the parameters for the URL.
  var parameters = {
    id: productId
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
  var productIdOfClicked = productClicked.id;

  // Return the product's id.
  return productIdOfClicked;

}


// Redirect user to the Product page
function renderProductPage(productIdentificationNumber) {

  // Set product parameters
  var parameters = {
    id: productIdentificationNumber
  }

  // Render the product page with the selected product name and id.
  window.location.replace(Flask.url_for("render_product_page", parameters));

}


// Display the product information on the page
function displayProduct(jsonOfProductInfo) {

  // Store JavaScript Object Notation JSON
  // in a variable to access later.
  var productJsonInfo = jsonOfProductInfo;


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



  // v v v Set content. v v v

  // Set product name.
  prodPageName.textContent = productJsonInfo['product_name'];
  // Set id of product name.
  prodPageName.setAttribute('id', productJsonInfo['id']);
  // TODO: Set a link to the product's website info.
  // e.g. A patagonia sweater should link to Patagonia's page for the product.

  // Set brand.
  prodPageBrand.textContent = productJsonInfo['brand'];

  // Set product image.
  prodPageImage.setAttribute('src', productJsonInfo['image']);

  // Set price (to two decimal places).
  prodPagePrice.textContent = "$" + productJsonInfo['price'].toFixed(2);

  // Set description.
  prodPageDescription.textContent = productJsonInfo['description'];

  // Set characteristics.
  // Populate with empty state values
  // until characteristics are available.
  prodPageCharacteristics.textContent = "This section is under construction.";
    // TODO: Create characteristics in DB.
    // See the productJSON.html note
    // for details about structure.

  // Remove any of the old references on screen.
  var oldReferencesToRemove = document.querySelector('.references-list');

  if (oldReferencesToRemove != null) {
    while (oldReferencesToRemove.firstChild) {
      oldReferencesToRemove.removeChild(oldReferencesToRemove.firstChild);
    }
  }


  // Check for references.
  if (productJsonInfo['reference_titles'].length > 0) {

    // Loop through all references for product.
    for (var i = 0; i < productJsonInfo['reference_titles'].length; i++) {

      // Set references.
      // Create list item.
      var referenceListItem = document.createElement('li');

      // Set the id of this reference to correspond to the id in our database
      referenceListItem.setAttribute('id', 'reference-id-' + productJsonInfo['reference_ids'][i]);

      // Create reference variable.
      // Make it an anchor element.
      var referenceItemContent = document.createElement('a');
      // Set the anchor element's id to be unique and descriptive
      referenceItemContent.setAttribute('id', 'link-to-reference-' + productJsonInfo['reference_ids'][i]);
      // Set text content to title.
      referenceItemContent.textContent = productJsonInfo['reference_titles'][i];
      // Set href attribute to link.
      referenceItemContent.setAttribute("href", productJsonInfo['reference_links'][i]);
      // Append to the list item.
      referenceListItem.appendChild(referenceItemContent);

      // Append list items to ordered list.
      prodPageReferences.appendChild(referenceListItem);

    }
  } else {

    // Select the references area.
    var referenceSection = document.querySelector('.references');

    // Check for a pre-existing empty state.
    if (!(referenceSection.querySelector('#reference-empty-state'))) {

      console.log('')
      console.log('There is no reference empty state. Adding one now...')

      // Create content for an empty state.
      var referenceEmptyStateText = document.createElement('p');
      // Tell the user why the references section is empty.
      referenceEmptyStateText.textContent = 'No references yet. Please add some. :)';

      // Set the element id.
      referenceEmptyStateText.setAttribute('id', 'reference-empty-state');

      // Add the empty state to the page.
      referenceSection.appendChild(referenceEmptyStateText);
    } else {

      console.log('')
      console.log('Already a reference empty state. Moving on...')

    }

  }

  if (!(document.querySelector('#edit-product'))) {
    // Insert a save button at the end of the form.
    insertEditButton();
    // Listen for edit requests.
    listenForEditRequests();
  }

};

// Listen for edit requests
function listenForEditRequests() {

  return new Promise((resolve,reject) => {
    // Find the edit button element.
    var editButton = document.querySelector('#edit-product');
    // On click, display edit forms.
    editButton.addEventListener('click', renderEditInterface, {once:false});
  })

}

// Render "edit product info" UI.
function renderEditProductForm() {

  // TODO: Create form elements for all the required page elements.
  // Submit the form via the POST method.

  return new Promise((resolve, reject) => {

    // Select all the product elements (could be own function).
    // It is used in the displayProduct code as well.

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
    // Select all list items in reference list.
    var referenceList = prodPageReferences.childNodes;

    // Store page elements into a map for easy access.
    var prodPageElements = new Map();

    // Set key / value pairs of the new Map.
    prodPageElements.set('name', prodPageName);
    prodPageElements.set('brand', prodPageBrand);
    prodPageElements.set('image', prodPageImage);
    prodPageElements.set('price', prodPagePrice);
    prodPageElements.set('description', prodPageDescription);
    prodPageElements.set('characteristics', prodPageCharacteristics);
    prodPageElements.set('references', referenceList);


    // Create an input element for each form.
    prodPageElements.forEach(function(value, key) {

      // Create a form element.
      var formElement = document.createElement('form');
      // Name the form.
      formElement.setAttribute('name', key + '-form');
      // Set the method to POST.
      formElement.setAttribute('method', 'POST');
      // POST to the url for editing the product.
      formElement.setAttribute('action', Flask.url_for('render_product_page'));

      // On the references form, loop through all the reference items.
      if (key === 'references') {

        // Loop through references.
        for(var i = 0; i < value.length; i++) {

          // Create a new form element.
          var formElement = document.createElement('form');
          // Name the form.
          formElement.setAttribute('name', 'reference-form');
          // Set the method to POST.
          formElement.setAttribute('method', 'POST');
          // POST to the url for editing the product.
          formElement.setAttribute('action', Flask.url_for('render_product_page'));
          // TODO: See if this form action can be removed
          // based on how we submit the XHR.


          // Create an input for the title of this reference.
          var titleInput = document.createElement('input');
          // Name the input.
          titleInput.setAttribute('name', 'reference-title-input-' + i);
          // Add placeholder text with current title.
          titleInput.setAttribute('placeholder', value[i].firstChild.innerText);
          // Give the input a class
          titleInput.setAttribute('class', 'product-edit-input');

          // Label the input field with an instructive title.
          // Create a label element.
          var labelTitle = document.createElement('label');
          // Link the label element to the appropriate input field.
          labelTitle.setAttribute('for', 'reference-title-input-' + i);
          // Set the label to be an informative one.
          labelTitle.textContent = 'Title';

          // Create an input for the link.
          var linkInput = document.createElement('input');
          // Name the input.
          linkInput.setAttribute('name', 'reference-link-input-' + i);
          // Add placeholder text with current title.
          linkInput.setAttribute('placeholder', value[i].firstChild.href);
          // Label the input field with an instructive title.
          linkInput.setAttribute('label', 'Link');
          // Give the input a class
          linkInput.setAttribute('class', 'product-edit-input');

          // Label the input field with an instructive title.
          // Create a label element.
          var labelLink = document.createElement('label');
          // Link the label element to the appropriate input field.
          labelLink.setAttribute('for', 'reference-title-input-' + i);
          // Set the label to be an informative one.
          labelLink.textContent = 'Link';


          // Append the labels to the inputs
          formElement.appendChild(labelTitle);
          // Append an input for the title.
          formElement.appendChild(titleInput);
          // Append the labels to the inputs
          formElement.appendChild(labelLink);
          // Append an input for the link.
          formElement.appendChild(linkInput);
          // Append the form to the product page element.
          value[i].appendChild(formElement);

          // Add a delete button to the reference hyperlink.
          var referenceHref = value[i].querySelector('a');
          insertDeleteButton(referenceHref);
        }

      } else {

        // Create input element.
        var inputElement = document.createElement('input');
        // Name the element.
        inputElement.setAttribute('name', key + '-input');
        // Give the input a class
        inputElement.setAttribute('class', 'product-edit-input');

        // Label the input field with an instructive title.
        // Create a label element.
        var label = document.createElement('label');
        // Link the label element to the appropriate input field.
        label.setAttribute('for', key + '-input');
        // Set the label to be an informative one.
        label.textContent = key;

        // On the image form, use the URL as a placeholder.
        if (key === 'image') {
          // Provide placeholder text of current src.
          inputElement.setAttribute('placeholder', value.src);

        // Otherwise, on all other elements use the innerText as a placeholder.
        } else {
          inputElement.setAttribute('placeholder', value.innerText);
        }

        // Append the labels to the inputs
        formElement.appendChild(label);
        // Append the input element to the form element.
        formElement.appendChild(inputElement);
        // Append the form to the product page element.
        value.appendChild(formElement);
      }
    });

    // TODO: Figure out why there is no image form rendered.
    // Right now the screen does not show a form for the image.

    // Update form values when users enters input.
    updateFormValues();

    resolve('Edit form successfully rendered!');
  });
}


function insertEditButton() {

  // Return a new promise when this resolves.
  return new Promise((resolve,reject) => {

    // Look for a the save button.
    var saveRequestElement = document.querySelector('#save-edits');

    // Check if a save button was found.
    if (saveRequestElement != null) {
      // Remove the save button and its child nodes.
      while (saveRequestElement.firstChild) {
        saveRequestElement.removeChild(saveRequestElement.firstChild);
      }
    }

    // Remove save button container.
    saveRequestElement.parentNode.removeChild(saveRequestElement);

    // Create an edit element.
    var editButton = document.createElement('input');
    editButton.setAttribute('id', 'edit-product');
    editButton.setAttribute('type', 'button');
    editButton.setAttribute('value', 'Edit');

    // Get the product page element.
    var productPage = document.querySelector('.product-page');
    // Append this button to the bottom of the product page.
    productPage.appendChild(editButton);

    // Resolve the promise.
    resolve("An edit button was created!");

  });

}

function insertSaveButton() {

  // Return a new promise when this resolves.
  return new Promise((resolve,reject) => {

    // Find the edit button.
    var editRequestElement = document.querySelector('#edit-product');

    // Remove the edit button and its child nodes.
    while (editRequestElement.firstChild) {
      editRequestElement.removeChild(editRequestElement.firstChild);
    }

    // Remove edit button container.
    editRequestElement.parentNode.removeChild(editRequestElement);

    // Create a save element.
    var saveButton = document.createElement('input');
    saveButton.setAttribute('id', 'save-edits');
    saveButton.setAttribute('type', 'button');
    saveButton.setAttribute('value', 'Save Edits');

    // Get the product page element.
    var productPage = document.querySelector('.product-page');
    // Append this button to the bottom of the product page.
    productPage.appendChild(saveButton);

    // Resolve the promise.
    resolve("A save button was created!");

  });

}

// Append a delete button to the elements.
function insertDeleteButton(appendToTheseElements) {

  // Return a new promise when this resolves.
  return new Promise((resolve,reject) => {

    if (appendToTheseElements instanceof NodeList) {

      // Go through each element in a node list.
      appendToTheseElements.forEach(
        function(currentValue, currentIndex, listObj) {
          // Create a delete button.
          var deleteButton = document.createElement('input');
          deleteButton.setAttribute('value', 'x');
          deleteButton.setAttribute('type', 'button');
          deleteButton.setAttribute('class', 'delete-element');

          if (appendToTheseElements.id != null) {
            deleteButton.setAttribute('id', 'delete-btn-for' + appendToTheseElements.id);
          }

          // TODO: Append the delete button to the anchor tag

          // Append the delete button to the element.
          this.appendChild(deleteButton);

        }
      );
    } else {
      // Create a delete button.
      var deleteButton = document.createElement('input');
      deleteButton.setAttribute('value', 'x');
      deleteButton.setAttribute('type', 'button');
      deleteButton.setAttribute('class', 'delete-element');

      if (appendToTheseElements.id != null) {
        deleteButton.setAttribute('id', 'delete-btn-for' + appendToTheseElements.id);
      }

      // Append the delete button to the element.
      appendToTheseElements.insertAdjacentElement('afterend', deleteButton);

      // Listen for clicks on the delete button.
      listenForDelete(deleteButton);
    }

    // Resolve the promise.
    resolve("Delete buttons have been created");
  });
}

// TODO Listen for clicks on the delete button.
function listenForDelete(deleteButton) {

  console.log('Create listener on delete button');
  deleteButton.addEventListener('click',
    function() {
      markReferenceForDeletion(deleteButton)
    },
    {once:true});

}


// TODO Save the reference items for deletion
// but only submit the removal requests with all the other edits.
function markReferenceForDeletion(deleteButtonClicked) {

  // Get the reference item to delete
  var referenceToDelete = deleteButtonClicked.parentNode;

  // Add strikethrough and red font color to the anchor element.
  var referenceHyperLink = referenceToDelete.querySelector('a');
  referenceHyperLink.setAttribute('class', 'marked-for-deletion');

  // Remove the delete button.
  deleteButtonClicked.parentNode.removeChild(deleteButtonClicked);

  // Hide the edit form.
  var editFormOfReference = referenceToDelete.querySelector('form');
  editFormOfReference.style.visibility = 'hidden';

  // Update the form values to "deleteReference"
  // The form info will be collected on save and deleted.
  var formFields = editFormOfReference.querySelectorAll('.product-edit-input');

  // For each of the form inputs, set the value to deleteReference.
  formFields.forEach(
    function(currentValue, currentIndex, listObj) {
        formFields[currentIndex].setAttribute('value', 'deleteReference');
      }
  );

}

function listenForSave() {

  // Find the save button on the DOM.
  var saveButton = document.querySelector('#save-edits');
  // Listen for clicks on the save button.
  saveButton.addEventListener('click', submitEditForm, {once:false});

  // Listen for clicks on the Enter key
  // Find the edit inputs
  var textFieldsWithEdits = document.querySelector('.product-edit-input');
  // Listen for when the user presses the Enter key
  textFieldsWithEdits.addEventListener('keyup', function(event) {
    event.preventDefault();
    if (event.keyCode === 13) {
        saveButton.click();
    }
  });

}

// Update the form values based on the user's input.
function updateFormValues() {

  // Select all the form inputs on screen.
  var inputsToEditProductInfo = document.querySelectorAll('input');

  // Go through each input element on the page.
  for (var i = 0; i < inputsToEditProductInfo.length; i++)

    // Listen for when the user enters information.
    inputsToEditProductInfo[i].addEventListener('input', function(){
      // If there is content in the input field,
      // then update the value to match.
      if (this.value.length) {
        inputsToEditProductInfo.value = this.value;
      }
    });
}

function submitEditForm() {

  console.log('The save button was clicked. Submitting changes.');

  // Look for all the places where a user can request edits.
  var inputsAvailableToUser = document.querySelectorAll('input');

  // Create an object to store any edits requested by our user.
  var editRequestsFromUser = {};

  // Find any requested edits from the user.
  for (var i = 0; i < inputsAvailableToUser.length; i++) {

    // If the input has a value, save the information.
    if (inputsAvailableToUser[i].value && inputsAvailableToUser[i].type == 'text') {

      // Identify which information the user would like to change.
      var infoToChange = inputsAvailableToUser[i].parentNode.name;

      // If it is not a reference, then store the info.
      if (!infoToChange.startsWith("reference-form")) {
        // Create a key. Set it equal to the form name.
        var itemToEdit = inputsAvailableToUser[i].parentNode.name;
        // Create a value. Store the users edits here.
        var requestedUpdateFromUser = inputsAvailableToUser[i].value;

        // Store this key-value pair into a single javascript object.
        // Then we can make a single request to our server.
        editRequestsFromUser[itemToEdit] = requestedUpdateFromUser;
      }
      // If the requested edit was for a reference,
      // then make an additional array to organize the data.
      else {
        // Make a javascript array to store our reference data into.
        // This will be the 'value' which corresponds to the reference 'key'.
        var editToThisReference = {};

        // If this edit is for a reference's title, save the title.
        if (inputsAvailableToUser[i].name.startsWith('reference-title')) {

          // Save the referenceId
          var referenceId = inputsAvailableToUser[i].parentNode.parentNode.id;

          // Append the reference id to our reference edits object.
          editToThisReference['referenceId'] = referenceId;

          // Save the title edit.
          var referenceTitle = inputsAvailableToUser[i].value;

          // Store this information in the array for this reference id.
          editToThisReference['referenceTitle'] = referenceTitle;

          // Check for requested changes to the link.
          if (inputsAvailableToUser[i+1].value) {

            // If there is a change to the link then save the change.
            var referenceLink = inputsAvailableToUser[i+1].value;

            // Store this information in the array for this reference id.
            editToThisReference['referenceLink'] = referenceLink;

            // Otherwise, do not save a link value.
          }

          // No need to check the link input item again.
          // Increment i to jump to the next relevant input.
          i++;
        }
        // Otherwise, if the requested edit corresponds to a reference's link,
        // only save the link.
        else {

          // Save the referenceId
          var referenceId = inputsAvailableToUser[i].parentNode.parentNode.id;

          // Append the reference id to our reference edits object.
          editToThisReference['referenceId'] = referenceId;

          // Save the link.
          var referenceLink = inputsAvailableToUser[i].value;
          // There is no change to this reference's title.

          // Store this information in the array for this reference id.
          editToThisReference['referenceLink'] = referenceLink;
        }

        // TODO Save the reference id into editToThisReference form.
        // TODO Save 'reference-form' as the key.

        // Find the reference id.
        // This will be how we determine which reference to update in our db.
        var referenceFormName = inputsAvailableToUser[i].parentNode.name;

        // Append this reference and it's corresponding edits to our storage.
        // The reference id will be the 'key'
        // The array which contains our title and link will be the 'value'.
        editRequestsFromUser[referenceFormName] = editToThisReference;
      }

    }

  }

  // Get the id of the product we want to edit
  var productHeader = document.querySelector('.product-name');
  var productIdParameter = productHeader.getAttribute('id');

  // Add the product's id to our request.
  // This tells the server which product to edit.
  editRequestsFromUser['product-id'] = productIdParameter;

  // Set the product id to be a parameter in our POST request.
  var parameters = {
    id: productIdParameter
  }

  // Send an XHR via POST to the python application at our desired URL.
  // The URL will probably be the /products URL still.
  var postToThisURL = Flask.url_for('render_product_page');

  // Use a declaritive variable name.
  console.log(editRequestsFromUser);
  var dataToPost = editRequestsFromUser;

  // Convert the JSON to a string.
  var stringVersion = JSON.stringify(dataToPost);

  var plainJavascriptObjectArray = {"product-id":"3"};
  var stringToTestFetch = JSON.stringify(plainJavascriptObjectArray);

  fetch(postToThisURL, {
    method: 'POST', // or 'PUT'
    body: stringVersion,
    headers: new Headers({
      'Content-Type': 'application/json'
    })
  }).then(res => res.json())
  .catch(error => console.error('Error:', error))
  .then(response => displayProduct(response));

  // TODO: When you resolve the promise for this submission,
  // re-render the page.
  // retrieveJSON(getSearchParams());
}

// TODO: Update the page to enter 'View Product' state.
// Call the displayProduct() function.
// Only call after the edits have been submitted
// and changes are saved to the database.
// Otherwise, the user will not get the latest data.




// TODO: Create function to close the edit interface when the user is done.



// TODO: Create generic page update function for interactive tasks.
