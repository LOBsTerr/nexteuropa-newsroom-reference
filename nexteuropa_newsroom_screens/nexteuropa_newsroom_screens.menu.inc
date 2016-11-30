<?php

/**
 * @file
 * Code for the nexteuropa newsroom screens menu hooks.
 */

/**
 * Implements hook_menu().
 */
function nexteuropa_newsroom_screens_menu() {
  $items['newsroom'] = [
    'page callback' => '_nexteuropa_newsroom_newsroom_page',
    'access arguments' => ['access content'],
    'type' => MENU_CALLBACK,
    'file' => 'nexteuropa_newsroom.pages.inc',
  ];
  $items['newsroom-rss'] = [
    'title' => 'Newsroom RSS feed',
    'description' => 'Newsroom RSS feed',
    'page callback' => '_nexteuropa_newsroom_newsroom_rss',
    'access arguments' => ['access content'],
    'type' => MENU_CALLBACK,
    'file' => 'nexteuropa_newsroom.pages.inc',
  ];
}
