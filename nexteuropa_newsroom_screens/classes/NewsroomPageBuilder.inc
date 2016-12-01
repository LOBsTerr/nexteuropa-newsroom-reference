<?php

/**
 * @file
 * Code for the NewsroomPageBuilder class.
 */

/**
 * NewsroomPageBuilder class.
 */
class NewsroomPageBuilder {
  /**
   * Builds agenda base on url params.
   *
   * @param string $view
   *   View (presentation type): schedule, month, week, day.
   * @param string $type_name
   *   Type url name.
   * @param string $topic_name
   *   Topic url name.
   * @param string $arg1
   *   Date param.
   * @param string $arg2
   *   Date param.
   * @param string $arg3
   *   Date param.
   *
   * @return object
   *   Agenda item.
   */
  public static function buildPageAgenda($view = NewsroomAgenda::AGENDA_VIEW_SCHEDULE, $type_name = NEXTEUROPA_NEWSROOM_ALL, $topic_name = NEXTEUROPA_NEWSROOM_ALL, $arg1 = NULL, $arg2 = NULL, $arg3 = NULL) {

    $agenda = NULL;
    $current_date = new DateTime();
    $type = NewsroomPageBuilder::getType($type_name);
    $topic = NewsroomPageBuilder::getTopic($topic_name);
    switch ($view) {
      case NewsroomAgenda::AGENDA_VIEW_MONTH:
        $month = NewsroomPageBuilder::getMonth($arg1);
        $year = NewsroomPageBuilder::getYear($arg2);
        $current_date->setDate($year, $month, 1);

        $agenda = new NewsroomAgendaMonth($type, $topic, $current_date);
        break;

      case NewsroomAgenda::AGENDA_VIEW_WEEK:
        $week = NewsroomPageBuilder::getWeek($arg1);
        $year = NewsroomPageBuilder::getYear($arg2);
        $current_date->setISODate($year, $week);

        $agenda = new NewsroomAgendaWeek($type, $topic, $current_date);
        break;

      case NewsroomAgenda::AGENDA_VIEW_DAY:
        $day = NewsroomPageBuilder::getDay($arg1);
        $month = NewsroomPageBuilder::getMonth($arg2);
        $year = NewsroomPageBuilder::getYear($arg3);
        $current_date->setDate($year, $month, $day);

        $agenda = new NewsroomAgendaDay($type, $topic, $current_date);
        break;

      default:
        $day = NewsroomPageBuilder::getDay($arg1);
        $month = NewsroomPageBuilder::getMonth($arg2);
        $year = NewsroomPageBuilder::getYear($arg3);

        $current_date->setDate($year, $month, $day);
        $agenda = new NewsroomAgendaSchedule($type, $topic, $current_date);

    }

    return $agenda;
  }

  /**
   * Builds Agenda item based on the current date.
   *
   * @param string $view
   *   View (presentation type): schedule, month, week, day.
   * @param string $type
   *   Newsroom type.
   * @param array $topics
   *   Newsroom topic.
   * @param object $date
   *   Current date.
   *
   * @return NewsroomAgenda|null
   *   Agenda item.
   */
  public static function buildAgenda($view, $type, $topics, $date, $operator = NEXTEUROPA_NEWSROOM_TOPIC_OPERATOR_OR) {
    $agenda = NULL;
    switch ($view) {
      case NewsroomAgenda::AGENDA_VIEW_MONTH:
        $agenda = new NewsroomAgendaMonth($type, $topics, $date);
        break;

      case NewsroomAgenda::AGENDA_VIEW_WEEK:
        $agenda = new NewsroomAgendaWeek($type, $topics, $date);
        break;

      case NewsroomAgenda::AGENDA_VIEW_DAY:
        $agenda = new NewsroomAgendaDay($type, $topics, $date);
        break;

      case NewsroomAgenda::AGENDA_VIEW_SCHEDULE_BLOCK:
        $agenda = new NewsroomAgendaBlockSchedule($type, $topics, $date, $operator);
        break;

      default:
        $agenda = new NewsroomAgendaSchedule($type, $topics, $date);

    }

    return $agenda;
  }

  /**
   * Validates and returns day number.
   *
   * @param string $value
   *   Day number.
   *
   * @return int
   *   Day number.
   */
  private static function getDay($value) {
    return preg_match('/^\d{1,2}$/', $value) ? (int) $value : NewsroomHelper::getFormatedDate('d');
  }

  /**
   * Validates and returns week number.
   *
   * @param string $value
   *   Day number.
   *
   * @return int
   *   Week number.
   */
  private static function getWeek($value) {
    return preg_match('/^\d{1,2}$/', $value) ? (int) $value : NewsroomHelper::getFormatedDate('W');
  }

  /**
   * Validates and returns month number.
   *
   * @param string $value
   *   Month number.
   *
   * @return int
   *   Month number.
   */
  private static function getMonth($value) {
    return preg_match('/^\d{1,2}$/', $value) ? (int) $value : NewsroomHelper::getFormatedDate('n');
  }

  /**
   * Validates and returns year number.
   *
   * @param string $value
   *   Year number.
   *
   * @return int
   *   Year number.
   */
  private static function getYear($value) {
    return preg_match('/^\d{4}$/', $value) ? (int) $value : NewsroomHelper::getFormatedDate('Y');
  }

  /**
   * Gets taxonomy term topic from url name.
   *
   * @param string $topic_url
   *   Topic taxonomy term name.
   *
   * @return object
   *   Taxonomy term object.
   */
  private static function getTopic($topic_url) {
    $topic = NewsroomPageBuilder::getTaxonomyTerm($topic_url, NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY);
    if ($topic) {
      // Try to find active menu.
      if ($path = NewsroomHelper::fetchActiveMenuPath($topic->tid)) {
        menu_tree_set_path('main-menu', $path);
      }
    }
    return $topic;
  }

  /**
   * Validates date.
   *
   * @param string $value
   *   Date string.
   *
   * @return string|null
   *   Date string.
   */
  private static function getDate($value) {
    return NewsroomHelper::checkDateFormat($value);
  }

  /**
   * Gets taxonomy term type from url name.
   *
   * @param string $type_url
   *   Type taxonomy term name.
   *
   * @return object
   *   Taxonomy term object.
   */
  private static function getType($type_url) {
    return NewsroomPageBuilder::getTaxonomyTerm($type_url, NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY);
  }

  /**
   * Gets taxonomy term from url name.
   *
   * @param string $taxonomy_term_url
   *   Taxonomy term url name.
   * @param string $vocabulary_name
   *   Vocabulary name.
   *
   * @return object
   *   Taxonomy term object.
   */
  private static function getTaxonomyTerm($taxonomy_term_url, $vocabulary_name) {
    return $taxonomy_term_url == NEXTEUROPA_NEWSROOM_ALL ? NULL : NewsroomHelper::getTermFromRequest($taxonomy_term_url, $vocabulary_name);
  }

  /**
   * Builds newsroom page object.
   *
   * @param string|int $type_url
   *   Newsroom type url part or tid.
   * @param string|int $topic_url
   *   Newsroom topic url or tid.
   * @param string|null $start_date
   *   Start date.
   * @param string|null $end_date
   *   End date.
   * @param string $ec_content
   *   EC content.
   *
   * @return NewsroomPage
   *   NewsroomPage object.
   */
  public static function buildNewsroomPage($type_url = NULL, $topic_url = NULL, $start_date = NULL, $end_date = NULL, $ec_content = NEXTEUROPA_NEWSROOM_EC) {
    $type = NewsroomPageBuilder::getType($type_url);
    $topic = NewsroomPageBuilder::getTopic($topic_url);
    $start_date = NewsroomPageBuilder::getDate($start_date);
    $end_date = NewsroomPageBuilder::getDate($end_date);
    return new NewsroomPage($type, $topic, $start_date, $end_date, $ec_content);
  }

}
