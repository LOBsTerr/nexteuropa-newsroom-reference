<?php
/**
 * @file
 * Nexteuropa_newsroom.features.inc.
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nexteuropa_newsroom_ctools_screens_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_views_api().
 */
function nexteuropa_newsroom_screens_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
