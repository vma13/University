# -*- coding: utf-8 -*-
class CoursesController < ApplicationController
  before_filter :check_admin_user, :except=>['index', 'show']

  def index
    @courses = Course.page(params[:page])
  end

  def show
    @course = Course.find(params[:id])
    @dis = Discipline.where('id = ?', @course.discipline_id).first
  end

  def new
    @course = Course.new
  end

  def edit
    @course = Course.find(params[:id])
  end

  def create
    @course = Course.new(params[:course])
    if @course.save
      redirect_to @course, :notice => 'Курс дисциплины добавлен.'
    else
      render :action => "new"
    end
  end

  def update
    @course = Course.find(params[:id])
    if @course.update_attributes(params[:course])
      redirect_to @course, :notice => 'Курс сохранен.'
    else
      render :action => "edit"
    end
  end

  def destroy
    @course = Course.find(params[:id])
    @course.destroy
    redirect_to courses_url, :notice => 'Курс удален.'
  end
end
