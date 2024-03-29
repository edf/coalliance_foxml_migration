<?php

/**
 * @file
 * A drush script for FoxML collection migration.  
 *           heavily borrowed from https://github.com/UCLALibrary/ucla_migration
 */

/**
 * Implements hook_drush_command().
 */
function coalliance_foxml_migration_drush_command() {
  $items = array();
  $items['foxml_save_pids_for_namespace'] = array(
    'callback' => 'coalliance_foxml_migration_save_pids_for_namespace',
    'description' => 'Gets all PIDS for the given namespace and saves them to a file.',
    'arguments' => array(
      'fedora_namespace' => "The Fedora namespace whose PIDS you're looking for.",
    ),
    'options' => array(),
    'examples' => array(
      'simple example' => 'drush -u 1 -l http://example.com foxml_save_pids_for_namespace your_namespace',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );

  $items['migrate_foxml2'] = array(
    'callback' => 'coalliance_migration_from_foxml2',
    'description' => 'Ingest content from foxml file for a single record.',
    'arguments' => array(
      'file_path' => 'The file path to the foxml file.',
      'fedora_namespace' => "The Fedora namespace to ingest the record under.",
      'dmdid' => "The record ID provided in the MODS for this particular record.",
    ),
    'options' => array(),
    'examples' => array(
      'simple example' => 'drush -u 1 -l http://example.com migrate_foxml /home/dgiuser/21198-zz00294nxr.xml codearl 21198-zz002bzvvs',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );
 $items['migrate_foxml3'] = array(
    'callback' => 'coalliance_migration_from_foxml3',
    'description' => 'Ingest content from foxml file for a single record.',
    'arguments' => array(
      'file_path' => 'The file path to the foxml file.',
      'fedora_namespace' => "The Fedora namespace to ingest the record under.",
      'dmdid' => "The record ID provided in the MODS for this particular record.",
    ),
    'options' => array(),
    'examples' => array(
      'simple example' => 'drush -u 1 -l http://example.com migrate_foxml /home/dgiuser/21198-zz00294nxr.xml codearl 21198-zz002bzvvs',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );

  $items['migrate_foxml'] = array(
    'callback' => 'coalliance_migration_from_foxml',
    'description' => 'Ingest content from foxml file for a single record.',
    'arguments' => array(
      'file_path' => 'The file path to the foxml file.',
      'fedora_namespace' => "The Fedora namespace to ingest the record under.",
      'dmdid' => "The record ID provided in the MODS for this particular record.",
    ),
    'options' => array(),
    'examples' => array(
      'simple example' => 'drush -u 1 -l http://example.com migrate_foxml /home/dgiuser/21198-zz00294nxr.xml codearl 21198-zz002bzvvs',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );
  return $items;
}

/**
 * Saves all pids in a Fedora namespace to a file.
 *
 * Output file is written to the coalliance_foxml_migration module folder.  It is given
 * the name of the fedora namespace and an extension of '.pid'.
 *
 * @param string $fedora_namespace
 *   The Fedora namespace of PIDS
 */
function coalliance_foxml_migration_save_pids_for_namespace($fedora_namespace) {
  // Get a connection to Fedora.
  $connection = islandora_get_tuque_connection();
  $repo = $connection->repository;

  // SPARQL query to get all objects in a given namespace.
  $query =
  "
    SELECT ?obj
    FROM <#ri>
    WHERE {
      ?obj <info:fedora/fedora-system:def/model#hasModel> ?model .
      FILTER(regex(str(?obj), '^info:fedora/$fedora_namespace:'))
    }
  ";

  // Execute the query.
  $results = $repo->ri->sparqlQuery($query);

  // Put all the pids in an array.
  $pids = array();
  foreach ($results as $result) {
    array_push($pids, $result['obj']['value']);
  }

  // JSON encode the array and write it to a file.
  $path = DRUPAL_ROOT . '/' . drupal_get_path('module', 'coalliance_foxml_migration') . "/$fedora_namespace.pids";
  $fp = fopen($path, 'w');
  if (!$fp) {
    drush_set_error("Can't open file to write",
      "Cannot open file $path to write.  Check your permissions for the coalliance_foxml_migration module folder or run this script using sudo.",
      "Error: "
    );
    return;
  }

  if (!fwrite($fp, json_encode($pids))) {
    drush_set_error("Can't write pids to file",
      "Cannot write pids to $path.  Check your permissions for the coalliance_foxml_migration module folder or run this script using sudo.",
      "Error: "
    );
    fclose($fp);
    return;
  }

  fclose($fp);
  return;
}

function coalliance_migration_from_foxml2($file_path, $fedora_namespace, $dmdid) {
  // Check to make sure the path to the foxml file has been provided.
  if (!isset($file_path)) {
    drush_set_error('File path not provided',
      'Path to FoxML file not provided as command line argument',
      'Error: ');
    return;
  }

  // Attempt to grab the foxml file.
  $foxml_file = file_get_contents($file_path);
  if (!$foxml_file) {
    drush_set_error('File not found',
      "Could not locate foxml file $file_path",
      "Error: ");
    return;
  }

#print_r($foxml_file);
#####$fedora_object->ingestDatastream($foxml_file);
$fedora_object = $foxml_file;
#$repository->ingestObject($fedora_object);

$my_islandora_tuque = new IslandoraTuque();
$repository = $my_islandora_tuque->repository;
$api_a = $repository->api->a; // For an Access API.
$api_m = $repository->api->m; // For a Management API.

#$datastreams = $api_a->listDatastreams('islandora:1');
#print_r($datastreams);

$test_pid = "wyu:9307";
$objectFormat = "info:fedora/fedora-system:FOXML-1.1";
$ingestMessage = array('string' => $foxml_file,
'label' => 'Fedora Label',
'format' => 'info:fedora/fedora-system:FOXML-1.1',
'encoding' => 'UTF-8',
'namespace' => 'islandora', 
'ownerID' => 'adrAdmin',
'logMessage' => 'Log message from ingest');




#$result_pid = $api_m->ingest('$test_pid',array('string' => '$file_path','format' => 'info:fedora/fedora-system:FOXML-1.1') );
$result_pid = $api_m->ingest($ingestMessage) ;

print_r($result_pid);

// $foxml is a string containing the requested XML.
#$pid = "islandora:1";
#$foxml = $api_m->export($pid,
#array('format' => 'info:fedora/fedora-system:FOXML-1.1',
#  'context' => 'migrate',
#  'encoding' => 'UTF-8')
#);
#print_r($foxml);


# from https://github.com/Islandora/islandora/wiki/Build,-Access,-Modify-and-Delete-Fedora-objects-with-the-Tuque-interface
// $foxml is a string containing the requested XML.
#$pid = "wyu:9307";
#$foxml = $repository->api->m->export($pid,
#array('format' => 'info:fedora/fedora-system:FOXML-1.1',
#  'context' => 'migrate',
#  'encoding' => 'UTF-8')
#);

}

function coalliance_migration_from_foxml3($file_path, $fedora_namespace, $dmdid) {
  // Check to make sure the path to the foxml file has been provided.
  if (!isset($file_path)) {
    drush_set_error('File path not provided',
      'Path to mets file not provided as command line argument',
      'Error: ');
    return;
  }
 
  // Attempt to grab the foxml file.
  $foxml_file = file_get_contents($file_path);
  if (!$foxml_file) {
    drush_set_error('File not found',
      "Could not locate foxml file $file_path",
      "Error: ");
    return;
  }
 
$fedora_object = $foxml_file;
/*
$my_islandora_tuque = new IslandoraTuque();
$repository = $my_islandora_tuque->repository;
$api_a = $repository->api->a; // For an Access API.
$api_m = $repository->api->m; // For a Management API.
*/
 
$connection = islandora_get_tugue_connection();
$repository = $connection->repository;
 
$object = $repository->constructObject($fedora_namespace);
 
$result_pid = $object; //test 1 to see if the object loads
//$result_pid = $repository->ingestObject($object); // test 2 to see if it ingests
 
/*
$test_pid = "wyu:9307";
$objectFormat = "info:fedora/fedora-system:FOXML-1.1";
$ingestMessage = "message";
 
$result_pid = $api_m->ingest($ingestMessage) ;
*/
print_r($result_pid);  //print the result
 
}

