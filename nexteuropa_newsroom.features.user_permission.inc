<?php

/**
 * @file
 * nexteuropa_newsroom.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function nexteuropa_newsroom_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer newsroom settings'.
  $permissions['administer newsroom settings'] = array(
    'name' => 'administer newsroom settings',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'nexteuropa_newsroom',
  );

  return $permissions;
}
