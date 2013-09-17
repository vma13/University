require 'test_helper'

class SgroupsControllerTest < ActionController::TestCase
  setup do
    @sgroup = sgroups(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:sgroups)
  end

  test "should get new" do
    get :new
    assert_response :success
  end

  test "should create sgroup" do
    assert_difference('Sgroup.count') do
      post :create, :sgroup => @sgroup.attributes
    end

    assert_redirected_to sgroup_path(assigns(:sgroup))
  end

  test "should show sgroup" do
    get :show, :id => @sgroup.to_param
    assert_response :success
  end

  test "should get edit" do
    get :edit, :id => @sgroup.to_param
    assert_response :success
  end

  test "should update sgroup" do
    put :update, :id => @sgroup.to_param, :sgroup => @sgroup.attributes
    assert_redirected_to sgroup_path(assigns(:sgroup))
  end

  test "should destroy sgroup" do
    assert_difference('Sgroup.count', -1) do
      delete :destroy, :id => @sgroup.to_param
    end

    assert_redirected_to sgroups_path
  end
end
