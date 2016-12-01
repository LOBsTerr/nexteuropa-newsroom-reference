<?php

/**
 * @file
 * Code for the NewsroomBuilder class.
 */

/**
 * NewsroomBuilder class.
 */
class NewsroomBuilder {
  /**
   * Builds newsroom importer generator.
   *
   * @param string $importer_id
   *   Importer ID.
   *
   * @return \NewsroomImporterGenerator
   *   Newsroom importer generator.
   */
  public static function buildImporter($importer_id) {
    switch ($importer_id) {
      case NEXTEUROPA_NEWSROOM_ITEM_IMPORTER:
        $title = 'Newsroom Items Multilingual';
        $description = 'Imports Newsroom Items from the Newsroom service.';
        $entity_type = 'node';
        $bundle = NEXTEUROPA_NEWSROOM_CONTENT_TYPE;
        $rss_context = '//channel/item';
        $import_period = -1;
        $field_mapping = NewsroomBuilder::getItemImporterMappings();
        break;

      case NEXTEUROPA_NEWSROOM_NEWSLETTER_IMPORTER:
        $title = 'Newsroom Newsletter issues';
        $description = 'Imports newsletter issues.';
        $entity_type = 'node';
        $bundle = NEXTEUROPA_NEWSROOM_NEWSLETTER_CONTENT_TYPE;
        $rss_context = '//channel/item';
        $import_period = 3600;
        $field_mapping = NewsroomBuilder::getIssueImporterMappings();
        break;

      case NEXTEUROPA_NEWSROOM_TYPE_IMPORTER:
        $title = 'Newsroom Type Multilingual';
        $description = 'Imports Item Types from the Newsroom service.';
        $entity_type = 'taxonomy_term';
        $bundle = NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY;
        $rss_context = '//channel/item';
        $import_period = -1;
        $field_mapping = NewsroomBuilder::getTypeImporterMappings();
        break;

      case NEXTEUROPA_NEWSROOM_TOPIC_IMPORTER:
        $title = 'Newsroom Topics Multilingual';
        $description = 'Imports Topics from the Newsroom service';
        $entity_type = 'taxonomy_term';
        $bundle = NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY;
        $rss_context = '//channel/item[infsonewsroom:BasicSvType="Newsroom service"]/category[@domain!="Newsletter" and @lang="' . NewsroomHelper::getDefaultLanguageUppercase() . '"]';
        $import_period = -1;
        $field_mapping = NewsroomBuilder::getTopicImporterMappings();
        break;

      case NEXTEUROPA_NEWSROOM_SERVICE_IMPORTER:
        $title = 'Newsroom Services Multilingual';
        $description = 'Imports Services from the Newsroom service.';
        $entity_type = 'taxonomy_term';
        $bundle = NEXTEUROPA_NEWSROOM_SERVICE_VOCABULARY;
        $rss_context = '//channel/item';
        $import_period = -1;
        $field_mapping = NewsroomBuilder::getServiceImporterMappings();
        break;
    }

    return new NewsroomImporterGenerator($importer_id, $field_mapping, $title, $description, $rss_context, $entity_type, $bundle, $import_period);
  }

  /**
   * Gets item importer field mapping settings.
   *
   * @return array
   *   Item importer field mapping settings.
   */
  private static function getItemImporterMappings() {

    $field_mapping = [
      [
        'field' => 'title',
        'query' => 'title[@lang="' . NewsroomHelper::getDefaultLanguageUppercase() . '"]/text()',
      ],
      [
        'field' => 'title_field',
        'query' => 'title',
      ],
      [
        'field' => 'field_newsroom_item_date:start',
        'query' => 'infsonewsroom:BasicDate/text()',
        'tamper' => [
          'plugin_id' => 'strtotime',
        ],
      ],
      [
        'field' => 'field_newsroom_item_date:end',
        'query' => 'infsonewsroom:BasictoDate/text()',
        'tamper' => [
          'plugin_id' => 'strtotime',
        ],
      ],
      [
        'field' => 'field_newsroom_private_img:uri',
        'query' => 'enclosure[@type="image/jpeg" and @schema="Private"]/@url',
      ],
      [
        'field' => 'field_newsroom_illustrative_img:uri',
        'query' => 'enclosure[@type="image/jpeg" and @schema="Public"]/@url',
      ],
      [
        'field' => 'field_newsroom_private_img:title',
        'query' => 'infsonewsroom:PicTitle',
        'original_field' => 'field_file_image_title_text',
      ],
      [
        'field' => 'field_newsroom_private_img:alt',
        'query' => 'infsonewsroom:PicAlt',
        'original_field' => 'field_file_image_alt_text',
      ],
      [
        'field' => 'field_newsroom_private_img:copyright',
        'query' => 'infsonewsroom:PicCopyright',
        'original_field' => 'field_newsroom_copyrights',
      ],
      [
        'field' => 'field_newsroom_private_img:caption',
        'query' => 'infsonewsroom:PicCaption',
        'original_field' => 'field_caption',
      ],
      [
        'field' => 'field_newsroom_illustrative_img:uri',
        'query' => 'enclosure[@type="image/jpeg" and @schema="Public"]/@url',
      ],
      [
        'field' => 'field_newsroom_illustrative_img:title',
        'query' => 'infsonewsroom:PicTitle',
        'original_field' => 'field_file_image_title_text',
      ],
      [
        'field' => 'field_newsroom_illustrative_img:alt',
        'query' => 'infsonewsroom:PicAlt',
        'original_field' => 'field_file_image_alt_text',
      ],
      [
        'field' => 'field_newsroom_illustrative_img:copyright',
        'query' => 'infsonewsroom:PicCopyright',
        'original_field' => 'field_newsroom_copyrights',
      ],
      [
        'field' => 'field_newsroom_illustrative_img:caption',
        'query' => 'infsonewsroom:PicCaption',
        'original_field' => 'field_caption',
      ],
      [
        'field' => 'field_newsroom_item_rapid_pr',
        'query' => 'infsonewsroom:BasicRapidPressRelease/text()',
      ],
      [
        'field' => 'field_newsroom_item_type',
        'query' => 'infsonewsroom:NewsType/@id',
        'options' => [
          'term_search' => '1',
          'autocreate' => 0,
        ],
        'tamper' => [
          'entity_type' => 'taxonomy_term',
          'plugin_id' => 'efq_finder',
          'bundle' => NEXTEUROPA_NEWSROOM_TYPE_VOCABULARY,
          'field' => 'field_newsroom_type_id',
        ],
      ],
      [
        'field' => 'field_tags',
        'query' => 'category[@domain="Policy" or @domain="Activity" or @domain="Theme" or @domain="Collection" or @domain="Tag"]/text()',
        'options' => [
          'term_search' => '0',
          'autocreate' => 0,
        ],
      ],
      [
        'field' => 'field_newsroom_item_id',
        'query' => 'infsonewsroom:BasicId',
        'unique' => 1,
      ],
      [
        'field' => 'field_newsroom_item_other_link:title',
        'query' => 'infsonewsroom:ContextOtherLinkText',
      ],
      [
        'field' => 'field_newsroom_item_other_link:url',
        'query' => 'infsonewsroom:ContextOtherLinkUrl',
      ],
      [
        'field' => 'field_newsroom_item_main_link:url',
        'query' => 'infsonewsroom:BasicUrl',
      ],
      [
        'field' => 'field_newsroom_documents:url',
        'query' => 'enclosure[not(@type="image/jpeg")]/@url',
      ],
      [
        'field' => 'field_newsroom_documents:title',
        'query' => 'enclosure[not(@type="image/jpeg")]/@title',
      ],
      [
        'field' => 'promote',
        'query' => 'infsonewsroom:pubHighlight/text()',
      ],
      [
        'field' => 'field_newsroom_topics',
        'query' => 'category[@domain!="Newsletter"]/@infsonewsroom:TopicId',
        'options' => [
          'term_search' => '1',
          'autocreate' => 0,
        ],
        'tamper' => [
          'plugin_id' => 'efq_finder',
          'entity_type' => 'taxonomy_term',
          'bundle' => NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY,
          'field' => 'field_newsroom_topic_id',
        ],
      ],
      [
        'field' => 'field_newsroom_primary_topic',
        'query' => 'category[@infsonewsroom:TopicPrimary="1" and @domain!="Newsletter"]/@infsonewsroom:TopicId',
        'options' => [
          'term_search' => '1',
          'autocreate' => 0,
        ],
        'tamper' => [
          'plugin_id' => 'efq_finder',
          'entity_type' => 'taxonomy_term',
          'bundle' => NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY,
          'field' => 'field_newsroom_topic_id',
        ],
      ],
      [
        'field' => 'created',
        'query' => 'infsonewsroom:BasicReferenceDate/text()',
        'tamper' => [
          'plugin_id' => 'strtotime',
        ],
      ],
      [
        'field' => 'sticky',
        'query' => 'infsonewsroom:pubIsCentral/text()',
      ],
      [
        'field' => 'field_newsroom_short_item',
        'query' => 'infsonewsroom:pubIsLong/text()',
      ],
      [
        'field' => 'field_newsroom_teaser_only',
        'query' => 'infsonewsroom:pubTeaserOnly/text()',
      ],
      [
        'field' => 'field_newsroom_related_content',
        'query' => 'infsonewsroom:slave/@id',
      ],
      [
        'field' => 'field_newsroom_parent_content',
        'query' => 'infsonewsroom:master/@id',
      ],
      [
        'field' => 'field_newsroom_project_acr',
        'query' => 'infsonewsroom:ContextProjectAcronym/text()',
      ],
      [
        'field' => 'field_newsroom_prj_coordinator',
        'query' => 'infsonewsroom:ContextProjectCoordinator/text()',
      ],
      [
        'field' => 'field_newsroom_project',
        'query' => 'infsonewsroom:ContextProjectName',
      ],
      [
        'field' => 'field_newsroom_project_website:url',
        'query' => 'infsonewsroom:ContextProjectURL',
      ],
      [
        'field' => 'field_newsroom_project_website:title',
        'query' => 'infsonewsroom:ContextProjectURLDisplay',
      ],
      [
        'field' => 'field_newsroom_location:wkt',
        'query' => 'infsonewsroom:ContextWellknowntext/text()',
      ],
      [
        'field' => 'field_newsroom_highlighted_topic',
        'query' => 'category[@infsonewsroom:TopicHighlight="1" and @domain!="Newsletter"]/@infsonewsroom:TopicId',
        'options' => [
          'term_search' => '1',
          'autocreate' => 0,
        ],
        'tamper' => [
          'plugin_id' => 'efq_finder',
          'entity_type' => 'taxonomy_term',
          'bundle' => NEXTEUROPA_NEWSROOM_TOPIC_VOCABULARY,
          'field' => 'field_newsroom_topic_id',
        ],
      ],
      [
        'field' => 'field_newsroom_ec_content',
        'query' => 'infsonewsroom:ContextECContent/text()',
      ],
      [
        'field' => 'field_newsroom_item_venue',
        'query' => 'infsonewsroom:ContextVenue',
      ],
      [
        'field' => 'field_newsroom_organiser',
        'query' => 'infsonewsroom:ContextOrganiser',
      ],
      [
        'field' => 'field_newsroom_author',
        'query' => 'infsonewsroom:ContextAuthor',
      ],
      [
        'field' => 'field_newsroom_eur_lex_link:url',
        'query' => 'infsonewsroom:ContextEurlex',
      ],
      [
        'field' => 'field_newsroom_ted_link:url',
        'query' => 'infsonewsroom:ContextTed',
      ],
      [
        'field' => 'field_newsroom_registration_link:url',
        'query' => 'infsonewsroom:ContextRegistrationLink',
      ],
      [
        'field' => 'field_newsroom_registration_link:title',
        'query' => 'infsonewsroom:ContextRegistrationLinkText',
      ],
      [
        'field' => 'body',
        'query' => 'infsonewsroom:FullContent',
      ],
      [
        'field' => 'field_newsroom_item_contact_text',
        'query' => 'infsonewsroom:ContextContactText',
      ],
      [
        'field' => 'field_newsroom_item_contact_mail',
        'query' => 'infsonewsroom:ContextContactEmail',
      ],
      [
        'field' => 'field_newsroom_item_linked_obj',
        'query' => 'infsonewsroom:FullLinkedObject',
      ],
      [
        'field' => 'field_newsroom_item_pre_title',
        'query' => 'infsonewsroom:FullPreTitle',
      ],
      [
        'field' => 'field_newsroom_item_quote_box',
        'query' => 'infsonewsroom:FullQuoteBox',
      ],
      [
        'field' => 'field_newsroom_item_short_title',
        'query' => 'infsonewsroom:BasicShortTitle',
      ],
      [
        'field' => 'field_newsroom_item_speaker',
        'query' => 'infsonewsroom:ContextSpeaker',
      ],
      [
        'field' => 'field_newsroom_teaser',
        'query' => 'infsonewsroom:BasicTeaser',
      ],
      [
        'field' => 'guid',
        'query' => '$field_newsroom_item_id',
      ],
      [
        'field' => '_feed_changed',
        'query' => 'infsonewsroom:pubUpdateDate/text()',
        'tamper' => [
          'plugin_id' => 'strtotime',
        ],
      ],
      [
        'field' => 'field_newsroom_newsletter_only',
        'query' => 'infsonewsroom:itemDisplay/text()',
      ],
      [
        'field' => 'field_newsroom_docsroom_ids',
        'query' => 'enclosure[@external_app="docsroom"]/@external_id',
      ],
      [
        'field' => 'language',
        'source' => 'Blank source 1',
        'tamper' => [
          'plugin_id' => 'default_value',
          'default_value' => NewsroomHelper::getDefaultLanguage(),
        ],
      ],
    ];

    return $field_mapping;
  }

  /**
   * Gets issue importer field mapping settings.
   *
   * @return array
   *   Issue importer field mapping settings.
   */
  private static function getIssueImporterMappings() {
    $field_mapping = [
      [
        'field' => 'title',
        'query' => 'title[@lang="' . NewsroomHelper::getDefaultLanguageUppercase() . '"]/text()',
      ],
      [
        'field' => 'title_field',
        'query' => 'title',
      ],
      [
        'field' => 'field_newsroom_nl_issue_date:start',
        'query' => 'pubDate/text()',
        'tamper' => [
          'plugin_id' => 'strtotime',
        ],
      ],
      [
        'field' => 'field_newsroom_newsletter_id',
        'query' => 'infsonewsroom:BasicIssueId/text()',
      ],
      [
        'field' => 'field_newsroom_item_main_link:url',
        'query' => 'link',
      ],
      [
        'field' => 'field_newsroom_newsletter_items:etid',
        'query' => 'infsonewsroom:BasicSvItemId/text()',
        'tamper' => [
          'plugin_id' => 'efq_finder',
          'entity_type' => 'node',
          'bundle' => 'newsroom_item',
          'field' => 'field_newsroom_item_id',
        ],
      ],
      [
        'field' => 'field_newsroom_service',
        'query' => 'infsonewsroom:BasicSvId/text()',
        'options' => [
          'term_search' => '1',
          'autocreate' => 0,
        ],
        'tamper' => [
          'entity_type' => 'taxonomy_term',
          'plugin_id' => 'efq_finder',
          'bundle' => NEXTEUROPA_NEWSROOM_SERVICE_VOCABULARY,
          'field' => 'field_newsroom_service_id',
        ],
      ],
      [
        'field' => 'guid',
        'query' => '$field_newsroom_newsletter_id',
        'unique' => 1,
      ],
      [
        'field' => 'language',
        'source' => 'Blank source 1',
        'tamper' => [
          'plugin_id' => 'default_value',
          'default_value' => NewsroomHelper::getDefaultLanguage(),
        ],
      ],
    ];

    return $field_mapping;
  }

  /**
   * Gets type importer field mapping settings.
   *
   * @return array
   *   Type importer field mapping settings.
   */
  private static function getTypeImporterMappings() {
    // Define the needed infos to build the importer dinamically.
    $field_mapping = [
      [
        'field' => 'guid',
        'query' => '@nrid',
        'unique' => 1,
      ],
      [
        'field' => 'field_newsroom_type_id',
        'query' => 'infsonewsroom:BasicTypeId/text()',
      ],
      [
        'field' => 'name',
        'query' => 'title[@lang="' . NewsroomHelper::getDefaultLanguageUppercase() . '"]/text()',
      ],
      [
        'field' => 'name_field',
        'query' => 'title',
      ],
      [
        'field' => 'parentguid',
        'query' => 'infsonewsroom:BasicTypeParent/text()',
        'tamper' => [
          'plugin_id' => 'rewrite',
          'prefix' => 'type-',
        ],
      ],
    ];

    return $field_mapping;
  }

  /**
   * Gets topic importer field mapping settings.
   *
   * @return array
   *   Topic importer field mapping settings.
   */
  private static function getTopicImporterMappings() {
    $field_mapping = [
      [
        'field' => 'Temporary target 1',
        'query' => '@infsonewsroom:TopicId',
        'target' => 'Temporary target 1',
      ],
      [
        'field' => 'guid',
        'query' => '@nrid',
        'unique' => 1,
      ],
      [
        'field' => 'field_newsroom_topic_id',
        'query' => '@infsonewsroom:TopicId',
      ],
      [
        'field' => 'name',
        'query' => 'text()',
      ],
      [
        'field' => 'name_field',
        'query' => 'text()',
      ],
      [
        'field' => 'field_newsroom_category_domain',
        'query' => '@domain',
      ],
      [
        'field' => 'parentguid',
        'query' => '@infsonewsroom:parentTopicId',
        'tamper' => [
          'plugin_id' => 'rewrite',
          'prefix' => 'topic-',
        ],
      ],
    ];

    return $field_mapping;
  }

  /**
   * Gets service importer field mapping settings.
   *
   * @return array
   *   Service importer field mapping settings.
   */
  private static function getServiceImporterMappings() {
    $field_mapping = [
      [
        'field' => 'guid',
        'query' => '@nrid',
        'unique' => 1,
      ],
      [
        'field' => 'field_newsroom_service_id',
        'query' => 'infsonewsroom:BasicSvId/text()',
      ],
      [
        'field' => 'name',
        'query' => 'title[@lang="' . NewsroomHelper::getDefaultLanguageUppercase() . '"]/text()',
      ],
      [
        'field' => 'name_field',
        'query' => 'title',
      ],
      [
        'field' => 'field_newsroom_service_active',
        'query' => 'infsonewsroom:BasicSvStatus/text()',
      ],
      [
        'field' => 'field_newsroom_service_sample:url',
        'query' => 'infsonewsroom:archivesLink',
      ],
      [
        'field' => 'field_newsroom_service_type',
        'query' => 'infsonewsroom:BasicSvType',
      ],
      [
        'field' => 'description',
        'query' => 'description/text()',
      ],
      [
        'field' => 'field_newsroom_basic_mailing',
        'query' => 'infsonewsroom:BasicSvMailing/text()',
      ],
      [
        'field' => 'field_newsroom_mailing_exists',
        'query' => 'infsonewsroom:mailingExists/text()',
      ],
      [
        'field' => 'field_newsroom_service_image:uri',
        'query' => 'infsonewsroom:BasicSvVisuUrl/text()',
      ],
      [
        'field' => 'parentguid',
        'query' => '@infsonewsroom:parentTopicId',
        'tamper' => [
          'plugin_id' => 'rewrite',
          'prefix' => 'service-',
        ],
      ],
    ];

    return $field_mapping;
  }

}
