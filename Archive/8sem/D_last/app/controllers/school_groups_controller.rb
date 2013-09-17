# -*- coding: utf-8 -*-
class SchoolGroupsController < ApplicationController
   before_filter :check_admin_user

  def index
    respond_to do |format|
      format.html{
        @school_groups = SchoolGroup.find_by_year(session[:choice_year].to_i).page(params[:page])
      }
      format.json do
        @school_groups = SchoolGroup.where("lower(number) LIKE lower(?)", "%#{params[:q]}%").all
        render :json => @school_groups.map(&:attributes)
      end
    end
  end

  def show
    @school_group = SchoolGroup.includes(:schoolkids).find(params[:id])
  end

  def new
    @school_group = SchoolGroup.new
  end

  def edit
    @school_group = SchoolGroup.find(params[:id])
  end

  def create
    @school_group = SchoolGroup.new(params[:school_group])
    school = School.where('id = ?',  @school_group.school_id).first
    @school_group.stype = school.stype
    @school_group.number += "-" + school.school_type? + "(" + school.number + ")"
    if @school_group.save
      redirect_to @school_group, :notice => 'Класс добавлен.'
    else
      render :action => "new"
    end
  end

  def update
    @school_group = SchoolGroup.find(params[:id])
    if @school_group.update_attributes(params[:school_group])
      redirect_to @school_group, :notice => 'Класс сохранен.'
    else
      render :action => "edit"
    end
  end

  def destroy
    @school_group = SchoolGroup.find(params[:id])
    @school_group.destroy
    redirect_to school_groups_url, :notice => 'Кдасс удален.'
  end
end
