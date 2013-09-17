require 'test_helper'

class LessonDatesControllerTest < ActionController::TestCase
  setup do
    @lesson_date = lesson_dates(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:lesson_dates)
  end

  test "should get new" do
    get :new
    assert_response :success
  end

  test "should create lesson_date" do
    assert_difference('LessonDate.count') do
      post :create, :lesson_date => @lesson_date.attributes
    end

    assert_redirected_to lesson_date_path(assigns(:lesson_date))
  end

  test "should show lesson_date" do
    get :show, :id => @lesson_date
    assert_response :success
  end

  test "should get edit" do
    get :edit, :id => @lesson_date
    assert_response :success
  end

  test "should update lesson_date" do
    put :update, :id => @lesson_date, :lesson_date => @lesson_date.attributes
    assert_redirected_to lesson_date_path(assigns(:lesson_date))
  end

  test "should destroy lesson_date" do
    assert_difference('LessonDate.count', -1) do
      delete :destroy, :id => @lesson_date
    end

    assert_redirected_to lesson_dates_path
  end
end
