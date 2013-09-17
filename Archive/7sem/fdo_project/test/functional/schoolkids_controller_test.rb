require 'test_helper'

class SchoolkidsControllerTest < ActionController::TestCase
  setup do
    @schoolkid = schoolkids(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:schoolkids)
  end

  test "should get new" do
    get :new
    assert_response :success
  end

  test "should create schoolkid" do
    assert_difference('Schoolkid.count') do
      post :create, :schoolkid => @schoolkid.attributes
    end

    assert_redirected_to schoolkid_path(assigns(:schoolkid))
  end

  test "should show schoolkid" do
    get :show, :id => @schoolkid.to_param
    assert_response :success
  end

  test "should get edit" do
    get :edit, :id => @schoolkid.to_param
    assert_response :success
  end

  test "should update schoolkid" do
    put :update, :id => @schoolkid.to_param, :schoolkid => @schoolkid.attributes
    assert_redirected_to schoolkid_path(assigns(:schoolkid))
  end

  test "should destroy schoolkid" do
    assert_difference('Schoolkid.count', -1) do
      delete :destroy, :id => @schoolkid.to_param
    end

    assert_redirected_to schoolkids_path
  end
end
