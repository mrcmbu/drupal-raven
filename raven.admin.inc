<?php

/**
 * @file
 * Administration form for the Raven authentication module.
 */

/**
 * Implements hook_form().
 */
function raven_settings_form($form, &$form_state) {
  global $base_url;

  $user1 = user_load(1);

  // Let the user override the standard login pages (user, user/login, ?q=user, ?q=user/login)
  $form['raven_login_override'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Raven login override'),
    '#default_value' => variable_get('raven_login_override'),
    '#description' => t('Override the \'@user_login_path\' and \'@user_path\' page with \'@raven_login_path\'. This means all logins must happen via Raven - site created users such as \'@user1\' will not be able to log in.<br /><i>Warning: Enabling this without having an administrator able to log in via Raven will lock you out of your site.</i><br />You can also perform this redirection with the built-in Path module.', array(
      '@user_login_path' => USER_LOGIN_PATH,
      '@user_path' => USER_PATH,
      '@raven_login_path' => RAVEN_LOGIN_PATH,
      '@user1' => $user1 ? $user1->name : 'admin',
      // user 1 should always exist, but just in case
    )),
  );

  $form['raven_backdoor_login'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Backdoor non-Raven login'),
    '#default_value' => variable_get('raven_backdoor_login'),
  );

  // Site description for Raven Login page
  $form['raven_website_description'] = array(
    '#type' => 'textfield',
    '#title' => t('Your website description'),
    '#default_value' => variable_get('raven_website_description'),
    // Get custom description, otherwise the site name, otherwise the site url
    '#description' => t('When Raven prompts the user to login it will display a message with the text <i>\'[...] This resource calls itself \'SITE DESCRIPTION\' and [...]</i>, where SITE DESCRIPTION is specified here. If left blank, the site name will be used (currently \'@sitename\').', array('@sitename' => variable_get('site_name', $base_url))),
  );

  // Site redirect if user fails to login
  $form['raven_login_fail_redirect'] = array(
    '#type' => 'textfield',
    '#title' => t('Login failure redirect'),
    '#field_prefix' => $base_url . '/',
    '#default_value' => variable_get('raven_login_fail_redirect'),
    '#description' => t('If a user fails login because their institution check fails, they will be redirected to the webpage above. If blank, the front page will be used.'),
    '#required' => FALSE,
  );

  return system_settings_form($form);
}