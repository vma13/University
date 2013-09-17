require 'test_helper'

class FSbjsControllerTest < ActionController::TestCase
  setup do
    @f_sbj = f_sbjs(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:f_sbjs)
  end

  test "should get new" do
    get :new
    assert_response :success
  end

  test "should create f_sbj" do
    assert_difference('FSbj.count') do
      post :create, :f_sbj => @f_sbj.attributes
    end

    assert_redirected_to f_sbj_path(assigns(:f_sbj))
  end

  test "should show f_sbj" do
    get :show, :id => @f_sbj.to_param
    assert_response :success
  end

  test "should get edit" do
    get :edit, :id => @f_sbj.to_param
    assert_response :success
  end

  test "should update f_sbj" do
    put :update, :id => @f_sbj.to_param, :f_sbj => @f_sbj.attributes
    assert_redirected_to f_sbj_path(assigns(:f_sbj))
  end

  test "should destroy f_sbj" do
    assert_difference('FSbj.count', -1) do
      delete :destroy, :id => @f_sbj.to_param
    end

    assert_redirected_to f_sbjs_path
  end
end
