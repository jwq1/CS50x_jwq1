// Google Map
// a reference (i.e., a pointer of sorts) to the map we’ll soon be instantiating;
var map;

// markers for map
// an array that will contain references to any markers we add atop the map;
var markers = [];

// marker labels
// an array of labels for the markers we will add
var labels = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
// an index to get each successive element in the array
// it enables the system to label each marker alphabetically
var labelIndex = 0;

// count which marker we are on
var markersIndex = 0;

// info window
// a reference to an "info window" in which we’ll ultimately display links to articles.
var info = new google.maps.InfoWindow();

// info's content
var infoWindowContent = [];


// execute when the DOM is fully loaded
    // anonymous function that will be called automatically by jQuery
    // when the mashup’s DOM is fully loaded
    // (i.e., when index.html and all its assets, CSS and JavaScript especially,
    // have been loaded into memory).

    // $() is shorthand for, "get the DOM node when ready"
        // In this case we are getting the top most parent node,
        // which is why no node is specified, only a function
        // Documentation http://learn.jquery.com/using-jquery-core/document-ready/
$(function() {

    // styles for map
    // https://developers.google.com/maps/documentation/javascript/styling
        // a definition of styles, an array of two objects
        // that we’ll use to configure our map
    // [  ] denote an array
    var styles = [

        // hide Google's labels
        // {  } denote an object
        {
            featureType: "all",
            elementType: "labels",
            stylers: [
                {visibility: "off"}
            ]
        },

        // hide roads
        {
            featureType: "road",
            elementType: "geometry",
            stylers: [
                {visibility: "off"}
            ]
        }

    ];

    // TODO: Get this from the user's input
        // innerHTML could help
        // jQueries getDocumentElementId() could help
        //
    // Make a variable for place
    map_placement_LatLng = {lat: 42.3770, lng: -71.1256}

    // options for map
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions
        // another collection of keys and values that
        // will ultimately be used to configure the map further
    var options = {
        center: map_placement_LatLng, // Cambridge, Massachusetts
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 14,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };

    // get DOM node in which map will be instantiated
    // $() is shorthand for, "get the DOM node with id=map-canvas, when ready"
        // Documentation http://learn.jquery.com/using-jquery-core/document-ready/
    // .get(), means jQuery will ask for the #map-canvas via a get request.
        // the 0, in .get(0) means it will get the first node with id of map-canvas
        // 0 is used here because there is only one map canvas (i.e. we want the first)
    var canvas = $("#map-canvas").get(0);

    // instantiate map
        // map, was set as a global variable in this script.js file (line 1)
        // new, means create another
        // google.map.Map(); is the class used to create a new map
            // it takes arguments of the div where the map will go
            // and the options we chose for the map
                // div is "canvas"
                // options is "options"
    map = new google.maps.Map(canvas, options);

    // configure UI once Google Map is idle (i.e., loaded)
        // google.maps.event is a class in Google Maps API
            // which listens for and handles events on the map
        // .addListenerOnce() listens for an event
            // at a particular place the "map", which is a class
            // extended from the MVC Object
            // when a particular event happens, "idle"
            // which is when everything is loaded
            // and then executes a function, "configure"
            // which is encapsulated later in this file
    google.maps.event.addListenerOnce(map, "idle", configure);


});

/**
 * Adds marker for place to map.
 */
// The update() function later in the program
// calls this addMarker function 10 times.
// this only needs to add one marker to the map
function addMarker(place)
{
    // TODO

    // get list of articles
    var parameters = {
        geo: place.postal_code

    };

    function getArticles(parameters, callback) {
        $.getJSON(Flask.url_for("articles"), parameters)
        .done(function(data, textStatus, jqXHR) {

            // var contentString = '<div>'
            // contentString += '<ul>';
            // for (var i = 0; i < 10; i++) {
            //     contentString += '<li><a href=' + data[i].link + '>' + data[i].title + '</a></li>';
            // }
            // contentString += '</ul></div>';

            // infoWindowContent.push(contentString);

            // info.setContent(contentString);
            // info.setContent(infoWindowContent[markersIndex]);


            // Variable used to store content for info window.
            // Content for the info window must come in the form of an html div
            var contentString = '<div>'
            // Within the div begin an unordered list.
            // The list will hold our list of articles.
            contentString += '<ul>';
            // .each is a method in jQuery to loop through arrays and objects
            // The method takes two arguments, the array/object
            // and a function indicating the index/object, or the key/value.
            $.each(data, function (index, object) {
                // only open 10 articles
                if (index < 10) {
                    $.each(data[index], function (key, value)  {
                        if (key == "link") {
                            contentString += '<li><a href=' + value + '>';
                        } else if (key == "title") {
                            contentString += value + '</a></li>';
                        }
                    });
                } else {
                    // exit .each loop
                    return false;
                }
            });
            contentString += '</ul></div>';

            // We put the .getJSON method into another function.
            // This function contains a callback as one of it's arguments
            // Call the callback here.
            // To undestand callbacks, click the following guide.
            // http://recurial.com/programming/understanding-callback-functions-in-javascript/
            callback(contentString);

            // DELETE: Irrelevant, to be deleted.
            infoWindowContent.push(contentString);



            // Logs to understand the .getJSON method

            // console.log(jqXHR);

            // // Check data output
            // for (var i = 0; i < 1; i++) {
            //     console.log('data[', i, ']');
            //     console.log(data[i]);
            // }

            // // Check textStatus output
            // console.log(textStatus);

            // // Check jqXHR.responseJSON output
            // for (var i = 0; i < 1; i++) {
            //     console.log('jqXHR.responseJSON[', i, ']');
            //     console.log(jqXHR.responseJSON[i]);
            // }


        })
        .fail(function(jqXHR, textStatus, errorThrown) {

            // log error to browser's console
            console.log(errorThrown.toString());
        });
    }

    // This function will be called when the callback
    // in our .getJSON method is called.
    // This code design ensures we only ask for the content
    // when it is ready.
    // Note:
    // .getJSON is asyncroneous.
    // If to access the .getJSON data,
    // we stored the data in a global variable.
    // there would be no guarantee
    // the variable would assigned it's .getJSON content
    // when we needed it.
    // Conclusion:
    // This function ensures we use the .getJSON data,
    // only after it is ready.
    // References:
    // http://recurial.com/programming/understanding-callback-functions-in-javascript/
    // getArticles(parameters, function(content) {
    //     infoWindowArticles = content;
    //     // console.log(content);
    //     // console.log(markersIndex + ' ' + infoWindowArticles);
    //     info.setContent(content);
    // });

    // info.setContent('test ' + markersIndex + ' iteration');
    // console.log(info);

    // var info = new google.maps.InfoWindow()

    // Place is an object from the database.
    // Parse our each object's latitude and longitude.
    // Turn the latitude and longitude values into a Float.
    // They start out as TEXT affinities in the database.
    // .Marker(position: ) requires a LatLngLiteral object
    // LatLngLiteral Object Specification: https://developers.google.com/maps/documentation/javascript/reference
    position_LatLng = {lat: parseFloat(place.latitude), lng: parseFloat(place.longitude)}

    var marker = new google.maps.Marker({
      position: position_LatLng,
      map: map,
      title: String(place.place_name),
      label: String(place.place_name),
      icon: {

          url: 'https://maps.gstatic.com/mapfiles/api-3/images/spotlight-poi-dotless_hdpi.png',
          labelOrigin: new google.maps.Point(21,95),
          // This marker is 20 pixels wide by 32 pixels high.
          size: new google.maps.Size(44, 88),
          // The origin for this image is (0, 0).
          origin: new google.maps.Point(0, 0),
          // The anchor for this image is the base of the flagpole at (0, 32).
          anchor: new google.maps.Point(22, 79)

        //   path: google.maps.SymbolPath.CIRCLE,

      }
    //   label: labels[labelIndex++ % labels.length]
    //   draggable: true
    });

    markers.push(marker);

    // showInfo(marker, contentString);

    marker.addListener('click', function() {

        info.setContent('<div><img alt=\'loading\' src=\'/static/ajax-loader.gif\'/></div>');

        getArticles(parameters, function(content) {
            info.setContent(content);
        });

       info.open(map, marker);
       console.log(info);

    });

    // count which marker we are on
    markersIndex += 1;

}

/**
 * Configures application.
 */
function configure()
{
    // update UI after map has been dragged
    google.maps.event.addListener(map, "dragend", function() {

        // if info window isn't open
        // http://stackoverflow.com/a/12410385
        if (!info.getMap || !info.getMap())
        {
            update();
        }
    });

    // update UI after zoom level changes
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });

    // configure typeahead
    // Reference CS50 Stack Exchange: https://cs50.stackexchange.com/questions/25201/pset-8-search-and-configure-functions/25202#25202
        // $() gets the object with id=q from the document
        // "#q" specifies the object with id=q
        // .typeahead is a method, of object "#q"
        // the .typahead method is given to object "#q"
            // because of the API we imported into our document
            // <!-- https://github.com/corejavascript/typeahead.js/blob/master/doc/jquery_typeahead.md -->
        // { } denotes an object,
            // in this case the object with id=q
            // is changed to have no highlight
                // highlight defaults to false, per documentation
            // and requires a minimum length of one
                // minLength: The minimum character length needed
                // before suggestions start getting rendered. Defaults to 1
    $("#q").typeahead({
        highlight: false,
        minLength: 1
    },
    {
        // Data set(s) compose the typeahead component
            // "display | displayKey " is a way to configure the dataset
            // It determines how to represent strings in the typeahead.
            // This is used after suggestion is selected.
            // It can be either a key string, or a function.
            // The function must turn the suggestion object into a string
            // https://github.com/corejavascript/typeahead.js/blob/master/doc/jquery_typeahead.md#datasets
            // "limit", is another configuration option to limit number of suggestions
            // "source", is the backing data source for suggestions
                // It is expected to be a function with the signature
                // (query, syncResults, asyncResults)
                // "search", is the function required by "source"
                    // the "search" function is encapsulated later in this file
            // "template", is a hash of templates to render datasets
                // a precompiled template is,
                // a function, which takes,
                // a Javascript object as its first argument,
                // then returns an HTML string
            // Handlebars.js is a framework to easily compile templates.
                // .compile, compiles a template,
                // which can be executed immediately.
            // {{place_name}}, {{admin_name1}}, {{postal_code}}
                // are variables which can be passed into the HTML template.
                // This functionality is enabled by Flask-JSGlue.

                // Flask-JSGlue is used to hook up our Flask application
                // with the front-end template.
                // Docs: http://stewartjpark.com/Flask-JSGlue/

                // We include Flask-JSGlue with a src tag in our index.html.
                // We also include JSGlue(app) in our application.py file.

                // By hooking up our Flask application with our front-end
                // we are able to pass in the variables
                // place_name, admin_name1, and postal_code
                // from our Flask application
        display: function(suggestion) { return null; },
        limit: 10,
        source: search,
        templates: {
            // suggestion, is used to render a suggestion.
            // It has to be a precompiled template.
            // Defaults to the value of "display"
            suggestion: Handlebars.compile(
                "<div>" +
                "{{place_name}}, {{admin_name1}}, {{postal_code}}" +
                "</div>"
            )
        }
    });

    // re-center map after place is selected from drop-down
        // when object with id=q is ready
        // .on() is a jQuery method
        // https://www.w3schools.com/jquery/event_on.asp
        // it accepts an event, in this case "typeahead:selected"
        // typeahead comes preloaded with custom events
        // these are triggered on the input element
        // typeahead:selected is fired when a suggestion is selected.
        // the event handler will be invoked with three arguments
            // the jQuery event object (i.e. DOM object with id=q)
            // the suggestion object that was selected (i.e. suggestion, set above)
            // the name of the dataset the suggestion belongs to ()
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {

        // set map's center
            // map.setCenter is a method used on the "map" object
            // the method comes from the Google Maps Javascript API
            // which we loaded in the index.html page
            // the method takes latitude and longitude.
            // since we saved those values as TEXT affinities in db
            // we need to use parseFloat to make the values into floating point values.
            // suggestion.latitude contains the latitude value from our suggestion.
            // The suggestion "source:" is "search", set above.
            // The search function will come more below.
        map.setCenter({lat: parseFloat(suggestion.latitude), lng: parseFloat(suggestion.longitude)});

        // update UI
            // the update() function comes later in this file.
        update();
    });

    // hide info window when text box has focus
        // why is function(eventData) listed here,
        // is the eventData coming from the q input field?
        // info is the eventObject, and close is a method used on that object.
        // info is set before the first function in this file.
        // var info = new google.map.InfoWindow();
    $("#q").focus(function(eventData) {
        info.close();
    });

    // re-enable ctrl- and right-clicking (and thus Inspect Element) on Google Map
    // https://chrome.google.com/webstore/detail/allow-right-click/hompjdfbfmmmgflfjdlnkohcplmboaeo?hl=en
    document.addEventListener("contextmenu", function(event) {
        event.returnValue = true;
        event.stopPropagation && event.stopPropagation();
        event.cancelBubble && event.cancelBubble();
    }, true);

    // update UI
    update();

    // give focus to text box
    $("#q").focus();
}

/**
 * Removes markers from map.
 */
function removeMarkers()
{
    // TODO
    // console.log(markers)
    // console.log(markers.length);

    for (var i = 0; i < markers.length; i++) {
        markers[i].setMap(null);
    }

    markers = [];

    // reset marker index
    markersIndex = 0;

    // reset info window content array
    infoWindowContent = [];

}

/**
 * Searches database for typeahead's suggestions.
 */
// this search function takes (query, syncResults, and asyncResults)
// as its arguments because search is used to assign the source: of typeahead
// look in the configure() > typeahead > display > source for more detail.
function search(query, syncResults, asyncResults)
{
    // get places matching query (asynchronously)
        // parameters is set here, to succinctly pass it
        // as an argument to $.getJSON below
        // q: query is used here, because our application
        // returns a JSON array via the /search?q=query URL
        // we cannot use q=query here, because Javascript would
        // interpret that as, "assign query to q".
    // $.getJSON accepts two arguments
        // the first is a path to where a JSON array can be found.
        // We could pass a direct path here, but we are dynamically changing
        // the path whenever we run a new query via GET request
        // We can address this challenge using the url_for method
        // provided by the Flask API
        // .url_for gets the path of the "search" function
        // in our Flask application (i.e. application.py)
        // then it appends parameters to that URL in the form of a query.
        // It does this by appending parameters after the ? in the URL
        // We happen to assign our query to the variable q,
        // rather than make a direct query
        // That is why we assign our parameters variable,
        // with an object q: query
    // .done & .fail
        // The jQuery method, .getJSON, can leverage Javascript promises
        // these promises can be linked to the end of the $.getJSON method.
        // .done, .fail, .always are available.
        // .done is the success path
        // .fail is the failed path
        // .always is used as a catch-all.
    // jqXHR, has documentation on the jQuery site.
    var parameters = {
        q: query
    };
    $.getJSON(Flask.url_for("search"), parameters)
    .done(function(data, textStatus, jqXHR) {

        // call typeahead's callback with search results (i.e., places)
        asyncResults(data);
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());

        // call typeahead's callback with no results
        asyncResults([]);
    });
}

/**
 * Shows info window at marker with content.
 */
function showInfo(marker, content)
{
    // start div
    var div = "<div id='info'>";
    if (typeof(content) == "undefined")
    {
        // http://www.ajaxload.info/
        div += "<img alt='loading' src='/static/ajax-loader.gif'/>";
    }
    else
    {
        div += content;
    }

    // end div
    div += "</div>";

    // set info window's content
    info.setContent(div);

    // // open info window (if not already open)
    // info.open(map, marker);

}

/**
 * Updates UI's markers.
 */
function update()
{
    // reset label index for new markers
    labelIndex = 0;

    // get map's bounds
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();

    // get places within bounds (asynchronously)
    var parameters = {
        ne: ne.lat() + "," + ne.lng(),
        q: $("#q").val(),
        sw: sw.lat() + "," + sw.lng()
    };
    $.getJSON(Flask.url_for("update"), parameters)
    .done(function(data, textStatus, jqXHR) {

       // remove old markers from map
       removeMarkers();

       // add new markers to map
       for (var i = 0; i < data.length; i++)
       {
           addMarker(data[i]);
        //   console.log(data[i]);
       }
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());
    });
};
